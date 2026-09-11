struct Spine4C660 { void* host; };
extern "C" {
void fn_8024C310(void*);
void fn_8024C660(void*, const Spine4C660* spine) { fn_8024C310(spine->host); }
}
