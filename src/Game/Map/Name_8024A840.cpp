#include <revolution.h>
struct Host4A840 { u32 field0;const char* name; };
struct Sensor4A840 { u8 opaque[0x24];Host4A840* host; };
struct Item4A840 { u8 opaque[0xc8];Sensor4A840* sensor; };
extern "C" const char* fn_8024A840(Item4A840* obj) {
 if(!obj->sensor)return 0;
 Host4A840* host=obj->sensor->host;
 if(!host)return 0;
 return host->name;
}
