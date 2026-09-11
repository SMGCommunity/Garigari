#include "LiveActor/LiveActor.hpp"
#include "LiveActor/LiveActorGroup.hpp"
struct Record503B0 { u8 opaque[16]; };
struct Actor503B0 { u8 opaque0[0x98]; LiveActorGroup* group98; u8 opaque9C[0x24]; void* childC0; Record503B0* records; };
struct Child503B0 : LiveActor { u8 opaque90[0xba]; u8 flag14A; };
struct Value503B0 { bool tag; u16 value; };
struct Calendar503B0 { s32 fields[10]; };
struct Display503B0 { const u16* name; s32 index, value8, valueC; bool flag10, flag11, flag12, flag13; const u16* date; const u16* time; s32 value1C; const u16* text; };
extern "C" {
s32 fn_8024F220(s32);
Value503B0* fn_8024C740(Value503B0*);
void fn_8024C670(u16*, const Value503B0*);
void fn_802510B0(Actor503B0*, Value503B0*, s32);
u64 fn_804DF130(const Record503B0*);
void fn_805BDE70(u64, Calendar503B0*);
void fn_8005F030(u16*, s32, s32, s32, s32);
void fn_8005F0A0(u16*, s32, s32, s32);
void fn_8005F110(u16*, s32, s32);
s32 fn_804DF150(const Record503B0*);
s32 fn_804DF080(const Record503B0*);
s32 fn_804DF090(const Record503B0*);
bool fn_804DF0D0(const Record503B0*);
s32 fn_802511B0(Actor503B0*, s32);
bool fn_80250F50(Actor503B0*, s32);
s32 fn_80251180(Actor503B0*, s32);
void fn_8046DB10(void*, const Display503B0*);
void fn_802503B0(Actor503B0* obj, s32 index) {
    Calendar503B0 calendar;
    u16 date[32], time[32], text[32];
    Display503B0 display;
    u16 name[12];
    if (static_cast<Child503B0*>(obj->group98->getActor(fn_8024F220(index)))->flag14A) {
        Value503B0 value;
        fn_8024C670(name, fn_8024C740(&value));
    } else {
        Value503B0 value;
        fn_8024C740(&value);
        fn_802510B0(obj, &value, index);
        fn_8024C670(name, &value);
    }
    fn_805BDE70(fn_804DF130(&obj->records[index - 1]), &calendar);
    fn_8005F030(date, 32, calendar.fields[5], calendar.fields[4] + 1, calendar.fields[3]);
    fn_8005F0A0(time, 32, calendar.fields[2], calendar.fields[1]);
    fn_8005F110(text, 32, fn_804DF150(&obj->records[index - 1]));
    display.name = name;
    display.index = index;
    display.value8 = fn_804DF080(&obj->records[index - 1]);
    display.valueC = fn_802511B0(obj, index);
    display.flag10 = fn_804DF090(&obj->records[index - 1]) >= 120;
    display.flag11 = fn_804DF0D0(&obj->records[index - 1]);
    display.flag12 = fn_80250F50(obj, index);
    display.flag13 = fn_804DF080(&obj->records[index - 1]) >= 242;
    display.date = date;
    display.time = time;
    display.value1C = fn_80251180(obj, index);
    display.text = text;
    fn_8046DB10(obj->childC0, &display);
}
}
