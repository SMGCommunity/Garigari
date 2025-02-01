#pragma once

#include "lyt/common.h"
#include "lyt/resources.h"
#include "ut/LinkList.h"
#include <revolution/types.h>

namespace nw4r {
    namespace lyt {
        class Pane;
        class Material;
        namespace res {
            struct AnimationBlock;
        };

        class AnimTransform {
        public:
            AnimTransform();

            virtual ~AnimTransform();
            virtual void SetResource(const res::AnimationBlock *, ResourceAccessor *) = 0;
            virtual void SetResource(const res::AnimationBlock *, ResourceAccessor *, u16) = 0;
            virtual void Bind(Pane *, bool, bool) = 0;
            virtual void Bind(Material *, bool) = 0;
            virtual void Animate(u32, Pane *) = 0;
            virtual void Animate(u32, Material *) = 0;

            ut::LinkListNode mLink;
            const res::AnimationBlock* mpRes;
            f32 mFrame;
        };

        class AnimTransformBasic : public AnimTransform {
        public:
            AnimTransformBasic();

            virtual ~AnimTransformBasic();
            virtual void SetResource(const res::AnimationBlock *, ResourceAccessor *) = 0;
            virtual void SetResource(const res::AnimationBlock *, ResourceAccessor *, u16) = 0;
            virtual void Bind(Pane *, bool, bool);
            virtual void Bind(Material *, bool);
            virtual void Animate(u32, Pane *);
            virtual void Animate(u32, Material *);

            void** mpFileResAry;
            AnimationLink* mAnimLinkAry;
            u16 mAnimLinkNum;
        };

        class AnimResource {
        public:
            AnimResource();

            const res::BinaryFileHeader* mpFileHeader;
            const res::AnimationBlock* mpResBlock;
            const res::AnimationTagBlock* mpTagBlock;
            const res::AnimationShareBlock* mpShareBlock;
        };
    };
};
