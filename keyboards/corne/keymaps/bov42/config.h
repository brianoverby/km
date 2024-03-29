#pragma once

// clang-format off
#define LAYOUT_bov42( \
        L00,  L01,  L02,  L03,  L04,  L05,         R05,  R04,  R03,  R02,  R01,  R00, \
        L10,  L11,  L12,  L13,  L14,  L15,         R15,  R14,  R13,  R12,  R11,  R10, \
        L20,  L21,  L22,  L23,  L24,  L25,         R25,  R24,  R23,  R22,  R21,  R20, \
                          L30,  L31,  L32,         R32,  R31,  R30                    \
    ) \
    LAYOUT_split_3x6_3( \
        L00,  L01,  L02,  L03,  L04,  L05,         R05,  R04,  R03,  R02,  R01,  R00, \
        L10,  L11,  L12,  L13,  L14,  L15,         R15,  R14,  R13,  R12,  R11,  R10, \
        L20,  L21,  L22,  L23,  L24,  L25,         R25,  R24,  R23,  R22,  R21,  R20, \
                          L30,  L31,  L32,         R32,  R31,  R30                    \
    )
// clang-format on