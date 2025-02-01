#include "lyt/animation.h"
#include "lyt/common.h"
#include "lyt/layout.h"
#include "lyt/pane.h"
#include "lyt/resources.h"
#include "revolution/mem/allocator.h"

namespace nw4r {
    namespace lyt {
        MEMAllocator* Layout::mspAllocator = nullptr;

        Layout::Layout() : mpRootPane(nullptr), mpGroupContainer(nullptr), mLayoutSize(0.0f, 0.0f) {

        }

        Layout::~Layout() {
            DeleteObj(mpGroupContainer);

            if (mpRootPane != nullptr && !mpRootPane->IsUserAllocated()) {
                DeleteObj(mpRootPane);
            }

            for (AnimTransformList::Iterator it = mAnimTransList.GetBeginIter(); it != mAnimTransList.GetEndIter();) {
                AnimTransformList::Iterator currIt = it++;
                mAnimTransList.Erase(currIt);
                DeleteObj(&(*currIt));
            }
        }

        bool Layout::Build(const void *lytResBuf, ResourceAccessor *pResAcsr) {
            const res::BinaryFileHeader *const pFileHead = static_cast<const res::BinaryFileHeader*>(lytResBuf);
            if (!detail::TestFileHeader(*pFileHead, 'RLYT')) {
                return false;
            }

            if (!detail::TestFileVersion(*pFileHead)) {
                return false;
            }

            ResBlockSet resBlockSet = { 0 };
            resBlockSet.pResAccessor = pResAcsr;
            Pane* pParentPane = nullptr;
            Pane* pLastPane = nullptr;
            bool bReadRootGroup = false;
            int groupNestLevel = 0;

            const void* dataPtr = static_cast<const u8*>(lytResBuf) + pFileHead->headerSize;
            for (int i = 0; i < pFileHead->dataBlocks; ++i) {
                const res::DataBlockHeader* pDataBlockHead = static_cast<const res::DataBlockHeader*>(dataPtr);
                switch (detail::GetSignatureInt(pDataBlockHead->kind)) {
                    case 'lyt1':
                    {
                        const res::Layout* pResLyt = static_cast<const res::Layout*>(dataPtr);
                        mLayoutSize = pResLyt->layoutSize;
                        break;
                    }
                    case 'txl1':
                        resBlockSet.pTextureList = static_cast<const res::TextureList*>(dataPtr);
                        break;
                    case 'fnl1':
                        resBlockSet.pFontList = static_cast<const res::FontList*>(dataPtr);
                        break;
                    case 'mat1':
                        resBlockSet.pMaterialList = static_cast<const res::MaterialList*>(dataPtr);
                        break;

                    case 'pan1':
                    case 'pic1':
                    case 'txt1':
                    case 'wnd1':
                    case 'bnd1':
                    {
                        Pane* pPane = BuildPaneObj(detail::GetSignatureInt(pDataBlockHead->kind), dataPtr, resBlockSet);

                        if (pPane != nullptr) {
                            if (mpRootPane == nullptr) {
                                mpRootPane = pPane;
                            }

                            if (pParentPane != nullptr) {
                                pParentPane->AppendChild(pPane);
                            }

                            pLastPane = pPane;
                        }
                    }
                    break;

                    case 'usd1':
                        pLastPane->SetExtUserDataList(reinterpret_cast<const res::ExtUserDataList*>(pDataBlockHead));
                        break;
                    case 'pas1':
                        pParentPane = pLastPane;
                        break;
                    case 'pae1':
                        pLastPane = pParentPane;
                        pParentPane = pLastPane->GetParent();
                        break;
                    case 'grp1':
                        {
                            if (!bReadRootGroup) {
                                bReadRootGroup = true;
                                mpGroupContainer = NewObj<GroupContainer>();
                            }
                            else {
                                if (mpGroupContainer != nullptr && groupNestLevel == 1) {
                                    if (Group* pGroup = NewObj<Group>(reinterpret_cast<const res::Group*>(pDataBlockHead), mpRootPane)) {
                                        mpGroupContainer->AppendGroup(pGroup);
                                    }
                                }
                            }
                            break;
                        }
                    case 'grs1':
                        groupNestLevel++;
                        break;
                    case 'gre1':
                        groupNestLevel--;
                        break;
                    default:
                        break;
                }

                dataPtr = static_cast<const u8*>(dataPtr) + pDataBlockHead->size;
            }

            return true;
        }

        /*
        AnimTransform* Layout::CreateAnimTransform() {
            const AnimTransformBasic* pAnimTrans = NewObj<AnimTransformBasic>();
            if (pAnimTrans != nullptr) {
                mAnimTransList.Push
            }
        }
        */

        void Layout::SetAnimationEnable(AnimTransform *pAnimTrans, bool bEnable) {
            if (mpRootPane != nullptr) {
                mpRootPane->SetAnimationEnable(pAnimTrans, bEnable, true);
            }
        }

        void Layout::CalculateMtx(const DrawInfo &rInfo) {
            if (mpRootPane == nullptr) {
                return;
            }

            mpRootPane->CalculateMtx(rInfo);
        }

        void Layout::Draw(const DrawInfo &rInfo) {
            if (mpRootPane == nullptr) {
                return;
            }

            mpRootPane->Draw(rInfo);
        }

        void Layout::Animate(u32 opt) {
            if (mpRootPane == nullptr) {
                return;
            }

            mpRootPane->Animate(opt);
        }

        
    };
};
