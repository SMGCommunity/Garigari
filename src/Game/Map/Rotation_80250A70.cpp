#include <JGeometry/TMatrix.hpp>
struct Child50A70 { u8 opaque0[0x20]; TVec3f rotation; };
struct Actor50A70 { u8 opaque0[0xf0]; Child50A70** children; s32 count; };
extern "C" {
extern const f32 lbl_807DC758, lbl_807DC75C, lbl_807DC760, lbl_807DC764, lbl_807DC768;
extern const f32 lbl_807DC720, lbl_807DC724, lbl_807DC728, lbl_807DC72C, lbl_807DC730, lbl_807DC734;
extern const u8 lbl_8074E9C0[];
void fn_80250CD0(TMtx34f*, f32, f32, f32);
void fn_80007060(TMtx34f*, const TMtx34f*);
void fn_80007680(TMtx34f*, const TMtx34f*);
void fn_80007380(TMtx34f*, const TMtx34f*, const TMtx34f*);
f32 fn_8053A9C0(const void*, f32, f32);
f32 fn_8000D7E0(f32);
void fn_80250A70(Actor50A70* obj) {
    const f32 scale = lbl_807DC758;
    const f32 inverseScale = lbl_807DC75C;
    TMtx34f first;
    first.identity();
    fn_80250CD0(&first, lbl_807DC760 * scale, lbl_807DC724, lbl_807DC764 * scale);
    fn_80007060(&first, &first);
    TMtx34f second;
    second.identity();
    fn_80250CD0(&second, lbl_807DC768 * scale, lbl_807DC724, lbl_807DC724);
    fn_80007680(&second, &first);
    Child50A70* child;
    for (s32 i = 0; i < obj->count; ++i) {
        TMtx34f matrix;
        matrix.identity();
        TVec3f rotation(obj->children[i]->rotation);
        rotation.scale(scale);
        fn_80250CD0(&matrix, rotation.x, rotation.y, rotation.z);
        fn_80007380(&matrix, &second, &matrix);
        child = obj->children[i];
        if (matrix.mMtx[2][0] - lbl_807DC720 >= lbl_807DC730) {
            child->rotation.x = fn_8053A9C0(lbl_8074E9C0, -matrix.mMtx[0][1], matrix.mMtx[1][1]);
            child->rotation.y = lbl_807DC734;
            child->rotation.z = lbl_807DC724;
        } else if (matrix.mMtx[2][0] + lbl_807DC720 <= lbl_807DC728) {
            { f32 secondArg = matrix.mMtx[1][1]; f32 firstArg = matrix.mMtx[0][1]; child->rotation.x = fn_8053A9C0(lbl_8074E9C0, firstArg, secondArg); }
            child->rotation.y = lbl_807DC72C;
            child->rotation.z = lbl_807DC724;
        } else {
            { f32 secondArg = matrix.mMtx[2][2]; f32 firstArg = matrix.mMtx[2][1]; child->rotation.x = fn_8053A9C0(lbl_8074E9C0, firstArg, secondArg); }
            { f32 secondArg = matrix.mMtx[0][0]; f32 firstArg = matrix.mMtx[1][0]; child->rotation.z = fn_8053A9C0(lbl_8074E9C0, firstArg, secondArg); }
            child->rotation.y = fn_8000D7E0(-matrix.mMtx[2][0]);
        }
        obj->children[i]->rotation.scale(inverseScale);
    }
}
}
