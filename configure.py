#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "SB4E01",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.3.0"
config.objdiff_tag = "v2.4.0"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym version={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-warn off"
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-i include",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

cflags_game = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,s",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-enc SJIS",
    "-sdata 4",
    "-sdata2 4",
    "-i include/Game",
    "-i libs/RVL_SDK",
    "-i libs/JSystem",
    "-i libs/MSL_C",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

cflags_sdk = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-enc SJIS",
    "-i libs/RVL_SDK",
    "-i libs/MSL_C",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

cflags_nw = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-enc SJIS",
    "-i libs/RVL_SDK",
    "-i libs/MSL_C",
    "-i libs/nw4r",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
    "-i libs/MSL_C",
    "-i libs/Runtime",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/2.6"

def GameLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": objects,
    }

def RVLLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_sdk,
        "progress_category": "sdk",
        "objects": objects,
    }

def NWLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.3",
        "cflags": cflags_nw,
        "progress_category": "nw4r",
        "objects": objects,
    }

Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(Matching, "Runtime/ptmf.c"),
            Object(NonMatching, "Runtime/runtime.c"),
            Object(NonMatching, "Runtime/global_destructor_chain.c"),
            Object(NonMatching, "Runtime/__init_cpp_exceptions.cpp"),
            Object(NonMatching, "Runtime/__mem.c"),
            Object(NonMatching, "Runtime/__va_arg.c"),
            Object(NonMatching, "Runtime/Gecko_ExceptionPPC.cpp"),
        ],
    },

    GameLib(
        "LiveActor",
        [
            Object(Matching, "Game/LiveActor/ActorSoundHolder.cpp"),
            Object(Matching, "Game/LiveActor/ActorStateBase.cpp"),
            Object(Matching, "Game/LiveActor/ActorStateKeeper.cpp"),
            Object(Matching, "Game/LiveActor/HitSensor.cpp"),
            Object(NonMatching, "Game/LiveActor/HitSensorInfo.cpp"),
            Object(Matching, "Game/LiveActor/HitSensorKeeper.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/LiveActor/LiveActor.cpp", extra_cflags=["-ipa file", "-DJGEOMETRY_INLINE_VEC3_CTOR", "-DJGEOMETRY_OUTLINE_VEC3_ADD"]),
            Object(Matching, "Game/LiveActor/LiveActorFlag.cpp"),
            Object(Matching, "Game/LiveActor/LiveActorGroup.cpp"),
            Object(NonMatching, "Game/LiveActor/LiveActorGroupArray.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/LiveActor/ModelManager.cpp"),
            Object(Matching, "Game/LiveActor/ModelObj.cpp"),
            Object(Matching, "Game/LiveActor/ModelObjDestructor.cpp"),
            Object(Matching, "Game/LiveActor/LodCtrl.cpp"),
            Object(NonMatching, "Game/LiveActor/RailRider.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDrawer.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceDrawer.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceOvalSupport.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceOval.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceOvalData.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeBoxSupport.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeBoxData.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeDrawerSupport.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeDrawerDraw.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeDrawerData.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeCylinderSupport.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeCylinderDraw.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeModelSupport.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSupport_80242160.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDraw_80242230.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSupport_80242490.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDraw_80242580.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSupport_80242820.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDraw_80242920.cpp"),
            Object(NonMatching, "Game/LiveActor/ShadowDraw_802429F0.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSupport_80242C60.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSupport_80242D30.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDraw_80242DA0.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDestructor_80242E80.cpp"),
            Object(Matching, "Game/LiveActor/ShadowCtor_80242EE0.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDraw_80242FD0.cpp"),
            Object(NonMatching, "Game/LiveActor/ShadowCallback_80243050.cpp"),
            Object(Matching, "Game/LiveActor/ShadowClone_80243080.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDestructor_802430F0.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeCylinderData.cpp"),
            Object(Matching, "Game/LiveActor/ShadowDestructor_80241350.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeDrawInitDestructor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeDrawInitCtor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeDrawerLength.cpp"),
            Object(NonMatching, "Game/LiveActor/ShadowVolumeDrawerPosition.cpp"),
            Object(Matching, "Game/LiveActor/ShadowVolumeBoxDestructor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceOvalDestructor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceDrawerDestructor.cpp"),
            Object(NonMatching, "Game/LiveActor/ShadowSurfaceCircle.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceCircleCtor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceCircleDestructor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceCircleData.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceBoxCtor.cpp"),
            Object(NonMatching, "Game/LiveActor/ShadowSurfaceBox.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceBoxSize.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceBoxDestructor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowSurfaceBoxData.cpp"),
            Object(Matching, "Game/LiveActor/Spine.cpp"),
            Object(NonMatching, "Game/LiveActor/Ctor_80243330.cpp"),
            Object(Matching, "Game/LiveActor/Control_80243460.cpp"),
            Object(Matching, "Game/LiveActor/Support_80243510.cpp"),
            Object(Matching, "Game/LiveActor/Support_80243580.cpp"),
            Object(Matching, "Game/LiveActor/Init_80243620.cpp"),
            Object(Matching, "Game/LiveActor/Support_80243780.cpp"),
            Object(Matching, "Game/LiveActor/Update_80243860.cpp"),
            Object(Matching, "Game/LiveActor/Ctor_80243990.cpp"),
            Object(Matching, "Game/LiveActor/Support_80243A90.cpp"),
            Object(NonMatching, "Game/LiveActor/Fade_80243B20.cpp"),
            Object(Matching, "Game/LiveActor/Update_80243BD0.cpp"),
            Object(Matching, "Game/LiveActor/Predicate_80243C60.cpp"),
            Object(Matching, "Game/LiveActor/Matrix_80243CF0.cpp"),
            Object(NonMatching, "Game/LiveActor/Matrix_80243F60.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/LiveActor/Support_802440B0.cpp"),
            Object(Matching, "Game/LiveActor/Init_802442B0.cpp"),
            Object(Matching, "Game/LiveActor/Support_802444F0.cpp"),
            Object(Matching, "Game/LiveActor/State_80244790.cpp"),
            Object(Matching, "Game/LiveActor/Support_80244960.cpp"),
            Object(Matching, "Game/LiveActor/Callback_80244BF0.cpp"),
            Object(Matching, "Game/LiveActor/Nerve_80244E70.cpp"),
            Object(Matching, "Game/LiveActor/Nerve_80244EB0.cpp"),
            Object(Matching, "Game/LiveActor/Switch_80244F10.cpp"),
            Object(Matching, "Game/LiveActor/Iterate_802450C0.cpp"),
            Object(Matching, "Game/LiveActor/Awake_80245220.cpp"),
            Object(Matching, "Game/LiveActor/Awake_802453C0.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerList.cpp"),
            Object(Matching, "Game/LiveActor/ShadowController.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerHolder.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerHolderCtor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerHolderDestructor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerFunction.cpp"),
            Object(Matching, "Game/LiveActor/SensorGroup.cpp"),
            Object(Matching, "Game/LiveActor/SensorHitChecker.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerVectorCtor.cpp"),
            Object(Matching, "Game/LiveActor/ShadowControllerVectorAppend.cpp"),
        ]
    ),

    GameLib(
        "Map",
        [
            Object(Matching, "Game/Map/CollisionCode.cpp"),
            Object(NonMatching, "Game/Map/RailGraph.cpp"),
            Object(Matching, "Game/Map/RailGraphEdge.cpp"),
            Object(Matching, "Game/Map/RailGraphIter.cpp"),
            Object(Matching, "Game/Map/RailGraphNode.cpp"),
            Object(Matching, "Game/Map/BezierRail.cpp"),
            Object(Matching, "Game/Map/BezierLength_80245A00.cpp", extra_cflags=["-ipa file"]),
            Object(NonMatching, "Game/Map/BezierParam_80245C10.cpp"),
            Object(Matching, "Game/Map/BezierNearest_80245D70.cpp"),
            Object(Matching, "Game/Map/BezierInit_80245E80.cpp"),
            Object(Matching, "Game/Map/BezierSupport_802460A0.cpp"),
            Object(Matching, "Game/Map/BezierCoord_802462B0.cpp"),
            Object(Matching, "Game/Map/BezierSection_802464E0.cpp"),
            Object(Matching, "Game/LiveActor/Actor_802467D0.cpp"),
            Object(Matching, "Game/LiveActor/Support_80246A20.cpp"),
            Object(NonMatching, "Game/LiveActor/Matrix_80246AF0.cpp"),
            Object(Matching, "Game/LiveActor/Sensor_80246BD0.cpp"),
            Object(Matching, "Game/LiveActor/Vector_80246C40.cpp"),
            Object(Matching, "Game/LiveActor/Vector_80246E40.cpp"),
            Object(Matching, "Game/LiveActor/State_80246FE0.cpp"),
            Object(Matching, "Game/LiveActor/State_80247130.cpp"),
            Object(Matching, "Game/LiveActor/State_80247220.cpp"),
            Object(Matching, "Game/LiveActor/Flag_80247290.cpp"),
            Object(Matching, "Game/LiveActor/Move_80247340.cpp"),
            Object(Matching, "Game/LiveActor/State_802474B0.cpp"),
            Object(Matching, "Game/LiveActor/Move_80247560.cpp"),
            Object(Matching, "Game/LiveActor/Move_80247670.cpp"),
            Object(Matching, "Game/LiveActor/Move_80247760.cpp"),
            Object(Matching, "Game/LiveActor/Move_80247850.cpp"),
            Object(NonMatching, "Game/LiveActor/State_80247900.cpp"),
            Object(Matching, "Game/LiveActor/Cleanup_802479A0.cpp"),
            Object(Matching, "Game/LiveActor/Nerve_80247A00.cpp"),
            Object(Matching, "Game/LiveActor/Nerve_80247A60.cpp"),
            Object(Matching, "Game/LiveActor/Holder_80247B40.cpp"),
            Object(NonMatching, "Game/LiveActor/Iterate_80247BE0.cpp"),
            Object(Matching, "Game/LiveActor/Group_80247CD0.cpp"),
            Object(Matching, "Game/LiveActor/Group_80247D70.cpp"),
            Object(Matching, "Game/LiveActor/Query_80247DF0.cpp"),
            Object(NonMatching, "Game/LiveActor/Query_80248020.cpp"),
            Object(Matching, "Game/LiveActor/Query_80248270.cpp"),
            Object(Matching, "Game/LiveActor/Query_802484D0.cpp"),
            Object(Matching, "Game/LiveActor/Query_80248790.cpp"),
            Object(Matching, "Game/LiveActor/Query_80248950.cpp"),
            Object(Matching, "Game/LiveActor/Bounds_80248AB0.cpp"),
            Object(Matching, "Game/LiveActor/Find_80248B40.cpp"),
            Object(Matching, "Game/LiveActor/Access_80248BC0.cpp"),
            Object(Matching, "Game/LiveActor/Group_80248C70.cpp"),
            Object(NonMatching, "Game/LiveActor/Bounds_80248D60.cpp"),
            Object(NonMatching, "Game/LiveActor/Bounds_80248F20.cpp"),
            Object(Matching, "Game/LiveActor/Bounds_80249010.cpp"),
            Object(Matching, "Game/LiveActor/Remove_802490F0.cpp"),
            Object(Matching, "Game/LiveActor/Cleanup_80249170.cpp"),
            Object(Matching, "Game/Map/CollisionDirector.cpp"),
            Object(Matching, "Game/Map/Init_80249FB0.cpp"),
            Object(Matching, "Game/Map/Setup_8024A0F0.cpp"),
            Object(Matching, "Game/Map/Scale_8024A1C0.cpp"),
            Object(Matching, "Game/Map/Group_8024A270.cpp"),
            Object(Matching, "Game/Map/Flags_8024A330.cpp"),
            Object(Matching, "Game/Map/Matrix_8024A3A0.cpp"),
            Object(Matching, "Game/Map/Update_8024A4A0.cpp"),
            Object(Matching, "Game/Map/Normalize_8024A5F0.cpp"),
            Object(Matching, "Game/Map/Access_8024A7B0.cpp"),
            Object(NonMatching, "Game/Map/Name_8024A840.cpp"),
            Object(Matching, "Game/Map/Index_8024A870.cpp"),
            Object(Matching, "Game/Map/Query_8024A880.cpp"),
            Object(Matching, "Game/Map/Query_8024AA30.cpp"),
            Object(Matching, "Game/Map/Query_8024AD00.cpp"),
            Object(Matching, "Game/Map/Query_8024AEB0.cpp"),
            Object(Matching, "Game/Map/Project_8024B070.cpp"),
            Object(Matching, "Game/Map/Plane_8024B3E0.cpp"),
            Object(Matching, "Game/Map/Query_8024B4A0.cpp"),
            Object(Matching, "Game/Map/Query_8024B690.cpp"),
            Object(Matching, "Game/Map/Query_8024B780.cpp"),
            Object(Matching, "Game/Map/Displacement_8024B890.cpp"),
            Object(Matching, "Game/Map/Actor_8024B920.cpp"),
            Object(Matching, "Game/Map/Init_8024B9A0.cpp"),
            Object(Matching, "Game/Map/Appear_8024BA00.cpp"),
            Object(Matching, "Game/Map/State_8024BAD0.cpp"),
            Object(Matching, "Game/Map/State_8024BB20.cpp"),
            Object(Matching, "Game/Map/Step_8024BC80.cpp"),
            Object(Matching, "Game/Map/Step_8024BD20.cpp"),
            Object(Matching, "Game/Map/Camera_8024BFF0.cpp"),
            Object(Matching, "Game/Map/Cleanup_8024C0C0.cpp"),
            Object(Matching, "Game/Map/Nerve_8024C120.cpp"),
            Object(Matching, "Game/Map/Nerve_8024C170.cpp"),
            Object(Matching, "Game/Map/Actor_8024C210.cpp"),
            Object(Matching, "Game/Map/Init_8024C260.cpp"),
            Object(Matching, "Game/Map/State_8024C2D0.cpp"),
            Object(NonMatching, "Game/Map/Step_8024C380.cpp"),
            Object(NonMatching, "Game/Map/Matrix_8024C430.cpp"),
            Object(Matching, "Game/Map/Cleanup_8024C570.cpp"),
            Object(Matching, "Game/Map/Nerve_8024C5D0.cpp"),
            Object(Matching, "Game/Map/Nerve_8024C610.cpp"),
            Object(Matching, "Game/Map/Nerve_8024C660.cpp"),
            Object(Matching, "Game/Map/Name_8024C670.cpp"),
            Object(Matching, "Game/Map/Value_8024C740.cpp"),
            Object(Matching, "Game/Map/Query_8024C7F0.cpp"),
            Object(Matching, "Game/Map/Actor_8024C8D0.cpp"),
            Object(Matching, "Game/Map/Init_8024CA30.cpp"),
            Object(Matching, "Game/Map/Lifecycle_8024CB00.cpp"),
            Object(Matching, "Game/Map/State_8024CC70.cpp"),
            Object(Matching, "Game/Map/Change_8024CD60.cpp"),
            Object(Matching, "Game/Map/Control_8024CE30.cpp"),
            Object(Matching, "Game/Map/Control_8024CED0.cpp"),
            Object(Matching, "Game/Map/Step_8024CFD0.cpp"),
            Object(Matching, "Game/Map/Step_8024D110.cpp"),
            Object(Matching, "Game/Map/Step_8024D220.cpp"),
            Object(Matching, "Game/Map/Matrix_8024D380.cpp"),
            Object(Matching, "Game/Map/Setup_8024D580.cpp"),
            Object(Matching, "Game/Map/Control_8024D7F0.cpp"),
            Object(NonMatching, "Game/Map/Motion_8024D8F0.cpp"),
            Object(NonMatching, "Game/Map/Appear_8024DF60.cpp"),
            Object(Matching, "Game/Map/Children_8024DFE0.cpp"),
            Object(Matching, "Game/Map/Effects_8024E0C0.cpp"),
            Object(Matching, "Game/Map/Helper_8024E3E0.cpp"),
            Object(NonMatching, "Game/Map/Factor_8024E440.cpp"),
            Object(Matching, "Game/Map/Helper_8024E560.cpp"),
            Object(Matching, "Game/Map/Control_8024E7B0.cpp"),
            Object(Matching, "Game/Map/Cleanup_8024EA60.cpp"),
            Object(Matching, "Game/Map/Nerve_8024EB80.cpp"),
            Object(Matching, "Game/Map/Nerve_8024EC10.cpp"),
            Object(Matching, "Game/Map/Actor_8024EDB0.cpp"),
            Object(Matching, "Game/Map/Cleanup_8024F080.cpp"),
            Object(Matching, "Game/Map/Nerve_8024F0E0.cpp"),
            Object(Matching, "Game/Map/Nerve_8024F120.cpp"),
            Object(NonMatching, "Game/Map/Lookup_8024F220.cpp"),
            Object(Matching, "Game/Map/Actor_8024F260.cpp"),
            Object(NonMatching, "Game/Map/Init_8024F320.cpp"),
            Object(Matching, "Game/Map/State_8024F490.cpp"),
            Object(Matching, "Game/Map/State_8024F580.cpp"),
            Object(NonMatching, "Game/Map/Positions_8024F5B0.cpp"),
            Object(Matching, "Game/Map/Query_8024F6F0.cpp"),
            Object(Matching, "Game/Map/Setup_8024F700.cpp"),
            Object(NonMatching, "Game/Map/Group_8024F7B0.cpp"),
            Object(NonMatching, "Game/Map/Callbacks_8024F900.cpp"),
            Object(NonMatching, "Game/Map/Callback_8024FA20.cpp"),
            Object(Matching, "Game/Map/Setup_8024FA60.cpp"),
            Object(Matching, "Game/Map/Setup_8024FBB0.cpp"),
            Object(Matching, "Game/Map/Group_8024FD70.cpp"),
            Object(Matching, "Game/Map/Control_8024FDF0.cpp"),
            Object(Matching, "Game/Map/Query_8024FE80.cpp"),
            Object(Matching, "Game/Map/Control_8024FEF0.cpp"),
            Object(Matching, "Game/Map/Group_8024FFA0.cpp"),
            Object(Matching, "Game/Map/Array_80250120.cpp"),
            Object(Matching, "Game/Map/Select_80250240.cpp"),
            Object(Matching, "Game/Map/Control_802502C0.cpp"),
            Object(Matching, "Game/Map/Display_802503B0.cpp"),
            Object(Matching, "Game/Map/Positions_80250570.cpp"),
            Object(Matching, "Game/Map/Create_802506F0.cpp"),
            Object(Matching, "Game/Map/Refresh_80250790.cpp"),
            Object(Matching, "Game/Map/Control_802508D0.cpp"),
            Object(Matching, "Game/Map/Rotation_80250A70.cpp"),
            Object(Matching, "Game/Map/Matrix_80250CD0.cpp"),
            Object(Matching, "Game/Map/Query_80250E20.cpp"),
            Object(Matching, "Game/Map/Value_80250FC0.cpp"),
            Object(Matching, "Game/Map/Query_80251180.cpp"),
            Object(Matching, "Game/Map/Control_80251340.cpp"),
            Object(NonMatching, "Game/Map/Group_80251430.cpp"),
            Object(Matching, "Game/Map/Setup_802515A0.cpp"),
            Object(Matching, "Game/Map/State_80251690.cpp"),
            Object(Matching, "Game/Map/State_80251850.cpp"),
            Object(Matching, "Game/Map/State_80251A50.cpp"),
            Object(Matching, "Game/Map/State_80251BB0.cpp"),
            Object(Matching, "Game/Map/State_80251CC0.cpp"),
            Object(Matching, "Game/Map/State_80251DD0.cpp"),
            Object(Matching, "Game/Map/State_80251E50.cpp"),
            Object(Matching, "Game/Map/State_80251F30.cpp"),
            Object(Matching, "Game/Map/State_80251FA0.cpp"),
            Object(Matching, "Game/Map/State_80252090.cpp"),
            Object(Matching, "Game/Map/State_80252120.cpp"),
            Object(Matching, "Game/Map/State_80252180.cpp"),
            Object(Matching, "Game/Map/State_80252270.cpp"),
            Object(Matching, "Game/Map/State_802523B0.cpp"),
            Object(Matching, "Game/Map/State_80252410.cpp"),
            Object(Matching, "Game/Map/State_80252470.cpp"),
            Object(Matching, "Game/Map/State_80252610.cpp"),
            Object(Matching, "Game/Map/State_80252690.cpp"),
            Object(Matching, "Game/Map/State_80252770.cpp"),
            Object(Matching, "Game/Map/State_80252800.cpp"),
            Object(Matching, "Game/Map/State_80252860.cpp"),
            Object(NonMatching, "Game/LiveActor/Init_80246850.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/Map/RailPart.cpp"),
            Object(Matching, "Game/Map/StageSwitch.cpp"),
            Object(Matching, "Game/Map/SwitchSynchronizer.cpp"),
            Object(Matching, "Game/Map/SwitchWatcher.cpp"),
            Object(Matching, "Game/Map/SwitchWatcherHolder.cpp", extra_cflags=["-ipa file"]),
        ]
    ),

    GameLib(
        "NameObj",
        [
            Object(Matching, "Game/NameObj/MovementOnOffGroupHolder.cpp"),
            Object(Matching, "Game/NameObj/NameObj.cpp"),
            Object(Matching, "Game/NameObj/NameObjAdaptor.cpp"),
            Object(Matching, "Game/NameObj/NameObjCategoryList.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/NameObj/NameObjGroup.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjFactory.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjFinder.cpp"),
            Object(Matching, "Game/NameObj/NameObjHolder.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/NameObj/NameObjRegister.cpp")
        ]
    ),

    GameLib(
        "Ride",
        [
            Object(NonMatching, "Game/Ride/TubeSlider.cpp"),
            Object(NonMatching, "Game/Ride/TubeSliderCoinCreator.cpp"),
            Object(Matching, "Game/Ride/TubeSliderCrystal.cpp"),
            Object(Matching, "Game/Ride/TubeSliderCrystalNrv.cpp"),
            Object(NonMatching, "Game/Ride/TubeSliderDamageObjCreator.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "Game/Ride/TubeSliderFunction.cpp"),
        ]
    ),

    GameLib(
        "System",
        [
            Object(Matching, "Game/System/NerveExecutor.cpp"),
            Object(Matching, "Game/System/ResourceInfo.cpp"),
            Object(Matching, "Game/System/ScenarioDataParser.cpp", extra_cflags=["-ipa file"]),
        ]
    ),

    GameLib(
        "Util",
        [
            Object(NonMatching, "Game/Util/ActorInitUtil.cpp"),
            Object(NonMatching, "Game/Util/ActorSensorUtil.cpp"),
            Object(NonMatching, "Game/Util/ActorShadowUtil.cpp"),
            Object(Matching, "Game/Util/JMapUtil.cpp"),
            Object(NonMatching, "Game/Util/LiveActorUtil.cpp"),
            Object(NonMatching, "Game/Util/MathUtil.cpp", extra_cflags=["-ipa file"]),
            Object(NonMatching, "Game/Util/MtxUtil.cpp"),
        ]
    ),

    RVLLib(
        "os",
        [
            Object(Matching, "RVL_SDK/os/OSFont.c"),
        ]
    ),

    NWLib(
        "nw4r_lyt",
        [
            Object(Matching, "nw4r/lyt/lyt_group.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_layout.cpp"),
        ]
    ),

    NWLib(
        "nw4r_ut",
        [
            Object(Matching, "nw4r/ut/ut_LinkList.cpp", extra_cflags=["-ipa file"]),
            Object(Matching, "nw4r/ut/ut_binaryFileFormat.cpp"),
            Object(Matching, "nw4r/ut/ut_CharStrmReader.cpp"),
            Object(NonMatching, "nw4r/ut/ut_TagProcessorBase.cpp"),
        ]
    ),
]

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("nw4r", "NintendoWare Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
