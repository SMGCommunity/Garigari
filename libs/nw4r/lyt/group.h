#pragma once

#include "ut/LinkList.h"
#include "lyt/pane.h"
#include "lyt/resources.h"
#include <cstddef>

namespace nw4r {
    namespace lyt {
        namespace detail {
            struct PaneLink {
                ut::LinkListNode mLink;
                Pane* mTarget;
            };
        };

        #ifdef __MWERKS__
        typedef ut::LinkList<detail::PaneLink, offsetof(detail::PaneLink, mLink)> PaneLinkList;
        #else
        typedef ut::LinkList<detail::PaneLink, 0>   PaneLinkList;
        #endif

        class Group {
        public:
            Group(const res::Group *, Pane *);

            virtual ~Group();

            const char* GetName() const {
                 return mName;
            }

            ut::LinkListNode mLink;
            PaneLinkList mPaneLinkList;
            char mName[17];
            u8 mbUserAllocated;
            u8 mPadding[2];
        };

        #ifdef __MWERKS__
        typedef ut::LinkList<Group, offsetof(Group, mLink)> GroupList;
        #else
        typedef ut::LinkList<Group, 0> GroupList;
        #endif

        class GroupContainer {
        public:
            ~GroupContainer();

            void AppendGroup(Group *);

            Group* FindGroupByName(const char *);

            GroupList mGroupList;
        };
    };
};
