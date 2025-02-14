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
            Object(NonMatching, "Runtime/ptmf.c"),
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
            Object(NonMatching, "Game/LiveActor/ActorStateKeeper.cpp"),
            Object(NonMatching, "Game/LiveActor/HitSensor.cpp"),
            Object(NonMatching, "Game/LiveActor/HitSensorInfo.cpp"),
            Object(NonMatching, "Game/LiveActor/HitSensorKeeper.cpp"),
            Object(NonMatching, "Game/LiveActor/LiveActor.cpp"),
            Object(NonMatching, "Game/LiveActor/LiveActorFlag.cpp"),
            Object(NonMatching, "Game/LiveActor/LiveActorGroup.cpp"),
            Object(NonMatching, "Game/LiveActor/LiveActorGroupArray.cpp"),
            Object(NonMatching, "Game/LiveActor/LodCtrl.cpp"),
            Object(NonMatching, "Game/LiveActor/RailRider.cpp"),
            Object(NonMatching, "Game/LiveActor/Spine.cpp"),
        ]
    ),

    GameLib(
        "Map",
        [
            Object(NonMatching, "Game/Map/CollisionCode.cpp"),
            Object(NonMatching, "Game/Map/RailGraph.cpp"),
            Object(NonMatching, "Game/Map/RailGraphEdge.cpp"),
            Object(NonMatching, "Game/Map/RailGraphIter.cpp"),
            Object(NonMatching, "Game/Map/RailGraphNode.cpp"),
            Object(NonMatching, "Game/Map/RailPart.cpp"),
            Object(NonMatching, "Game/Map/StageSwitch.cpp"),
            Object(NonMatching, "Game/Map/SwitchSynchronizer.cpp"),
            Object(NonMatching, "Game/Map/SwitchWatcher.cpp"),
        ]
    ),

    GameLib(
        "NameObj",
        [
            Object(NonMatching, "Game/NameObj/MovementOnOffGroupHolder.cpp"),
            Object(NonMatching, "Game/NameObj/NameObj.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjAdaptor.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjCategoryList.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjGroup.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjFactory.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjFinder.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjHolder.cpp"),
            Object(NonMatching, "Game/NameObj/NameObjRegister.cpp")
        ]
    ),

    GameLib(
        "System",
        [
            Object(NonMatching, "Game/System/NerveExecutor.cpp"),
            Object(NonMatching, "Game/System/ResourceInfo.cpp"),
            Object(NonMatching, "Game/System/ScenarioDataParser.cpp"),
        ]
    ),

    GameLib(
        "Util",
        [
            Object(NonMatching, "Game/Util/ActorInitUtil.cpp"),
            Object(NonMatching, "Game/Util/ActorSensorUtil.cpp"),
            Object(NonMatching, "Game/Util/JMapUtil.cpp"),
            Object(NonMatching, "Game/Util/LiveActorUtil.cpp"),
            Object(NonMatching, "Game/Util/MathUtil.cpp"),
            Object(NonMatching, "Game/Util/MtxUtil.cpp"),
        ]
    ),

    RVLLib(
        "os",
        [
            Object(NonMatching, "RVL_SDK/os/OSFont.c"),
        ]
    ),

    NWLib(
        "nw4r_lyt",
        [
            Object(NonMatching, "nw4r/lyt/lyt_group.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_layout.cpp"),
        ]
    ),

    NWLib(
        "nw4r_ut",
        [
            Object(NonMatching, "nw4r/ut/ut_LinkList.cpp"),
            Object(NonMatching, "nw4r/ut/ut_binaryFileFormat.cpp"),
            Object(NonMatching, "nw4r/ut/ut_CharStrmReader.cpp"),
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
