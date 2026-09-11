#include "LiveActor/LiveActor.hpp"
struct Nerve4F120 { const void* vtable; };
struct Spine4F120 { LiveActor* host; };
namespace MR { bool isFirstStep(const LiveActor*); void startAction(const LiveActor*, const char*); }
extern "C" {
void fn_8024EFD0(LiveActor*);
void fn_8024EF70(LiveActor*);
extern const char lbl_80696F94[], lbl_80696F84[];
extern const void* lbl_80697048[];
extern const void* lbl_80697038[];
extern const void* lbl_80697028[];
extern const void* lbl_80697018[];
Nerve4F120* fn_8024F120(Nerve4F120* obj) { obj->vtable = lbl_80697048; return obj; }
Nerve4F120* fn_8024F130(Nerve4F120* obj) { obj->vtable = lbl_80697038; return obj; }
Nerve4F120* fn_8024F140(Nerve4F120* obj) { obj->vtable = lbl_80697028; return obj; }
Nerve4F120* fn_8024F150(Nerve4F120* obj) { obj->vtable = lbl_80697018; return obj; }
void fn_8024F160(void*, const Spine4F120* spine) { fn_8024EFD0(spine->host); }
void fn_8024F170(void*, const Spine4F120* spine) { LiveActor* host = spine->host; if (MR::isFirstStep(host)) MR::startAction(host, lbl_80696F94); }
void fn_8024F1C0(void*, const Spine4F120* spine) { fn_8024EF70(spine->host); }
void fn_8024F1D0(void*, const Spine4F120* spine) { LiveActor* host = spine->host; if (MR::isFirstStep(host)) MR::startAction(host, lbl_80696F84); }
}
