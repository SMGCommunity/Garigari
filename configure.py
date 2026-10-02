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
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

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
config.ldflags = ["-fp hardware", "-nodefaults", "-warn off"]
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
    "-i libs/Runtime",
    "-i libs/MetroTRK",
    "-i libs/RVLFaceLib",
    "-i src/RVL_SDK/bte",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
    "-ir libs/RVL_SDK/revolution/bte",
    "-DREVOLUTION",
]

cflags_sdk_ipa = [
    *cflags_sdk,
    "-str reuse",
    "-lang=c",
    "-ipa file",
    "-fp_contract off",
    "-func_align 16",
]

cflags_sdk_exi = ["-O3" if flag == "-O4,p" else flag for flag in cflags_sdk]

cflags_sdk_gc = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto,level=3",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-str reuse",
    "-enc SJIS",
    "-ipa file",
    "-sdata 8",
    "-sdata2 8",
    "-i libs/RVL_SDK",
    "-i libs/MSL_C",
    "-i libs/Runtime",
    "-i libs/MetroTRK",
    "-i libs/RVLFaceLib",
    "-i src/RVL_SDK/bte",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
    "-ir libs/RVL_SDK/revolution/bte",
    "-DREVOLUTION",
]

cflags_nw = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    '-pragma "ppc_no_fp_blockmove on"',
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract off",
    "-str reuse",
    "-enc SJIS",
    "-ipa file",
    "-i libs/MSL_C++/include",
    "-i libs/MSL_C",
    "-i libs/MetroTRK",
    "-i libs/RVL_SDK",
    "-i libs/Runtime",
    "-i libs/nw4r/include",
    "-i libs/nw4r",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

cflags_jsys = [
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
    "-fp_contract off",
    "-str reuse",
    "-enc SJIS",
    "-sdata 4",
    "-sdata2 4",
    "-use_lmw_stmw off",
    "-i include",
    "-i libs/JSystem/include",
    "-i libs/RVL_SDK",
    "-i libs/MSL_C",
    "-i libs/MSL_C++/include",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

cflags_jsys_jaudio = [*cflags_jsys, "-ipa file", "-sym on"]
cflags_jsys_jpa = [*cflags_jsys, "-ipa file"]


cflags_rfl = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions on",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-str reuse",
    "-enc SJIS",
    "-ipa file",
    "-i libs/MSL_C",
    "-i libs/MetroTRK",
    "-i libs/RVL_SDK",
    "-i libs/Runtime",
    "-i libs/RVLFaceLib",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

cflags_msl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-fp_contract off",
    "-inline on",
    "-ipa file",
    "-func_align 4",
    "-i libs/MSL_C",
    "-i libs/RVL_SDK",
]

cflags_trk = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-func_align 4",
    "-pool off",
    "-i libs/MetroTRK",
    "-i libs/RVL_SDK",
    "-i libs/MSL_C",
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

config.linker_version = "GC/3.0a5"


def GameLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_game,
        "progress_category": "game",
        "objects": objects,
    }


def RVLLib(
    lib_name: str, objects: List[Object], cflags: List[str] = cflags_sdk_ipa
) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags,
        "progress_category": "sdk",
        "objects": objects,
    }


def RVLLibGC(
    lib_name: str, objects: List[Object], mw_version: str = "GC/3.0a3"
) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": mw_version,
        "cflags": cflags_sdk_gc,
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


def JSysLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_jsys,
        "progress_category": "jsys",
        "objects": objects,
    }


def JSys_JAudioLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_jsys_jaudio,
        "progress_category": "jsys",
        "objects": objects,
    }


def JSys_JParticleLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_jsys_jpa,
        "progress_category": "jsys",
        "objects": objects,
    }


def RFLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0",
        "cflags": cflags_rfl,
        "progress_category": "rfl",
        "objects": objects,
    }


def MSLLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.1",
        "cflags": cflags_msl,
        "progress_category": "msl",
        "objects": objects,
    }


def TRKLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.0a",
        "cflags": cflags_trk,
        "progress_category": "trk",
        "objects": objects,
    }


Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    JSysLib(
        "J2DGraph",
        [
            Object(
                NonMatching,
                "JSystem/J2DGraph/J2DGrafContext.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/J2DGraph/J2DOrthoGraph.cpp"),
            Object(NonMatching, "JSystem/J2DGraph/J2DMatBlock.cpp"),
            Object(NonMatching, "JSystem/J2DGraph/J2DPane.cpp"),
            Object(NonMatching, "JSystem/J2DGraph/J2DScreen.cpp"),
            Object(
                NonMatching,
                "JSystem/J2DGraph/J2DPicture.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(Matching, "JSystem/J2DGraph/J2DManage.cpp"),
        ],
    ),
    JSysLib(
        "J3DGraphAnimator",
        [
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DShapeTable.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DJointTree.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DModelData.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DMtxBuffer.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DModel.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DAnimation.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DMaterialAnm.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DSkinDeform.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DCluster.cpp",
                extra_cflags=["-ipa file"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DJoint.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphAnimator/J3DMaterialAttach.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
        ],
    ),
    JSysLib(
        "J3DGraphBase",
        [
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DGD.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching, "JSystem/J3DGraphBase/J3DSys.cpp", extra_cflags=["-ipa file"]
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DVertex.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DTransform.cpp",
                extra_cflags=["-ipa file", "-sym on", "-opt nolifetimes,nocse"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DPacket.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DShapeMtx.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DShapeDraw.cpp",
                extra_cflags=["-ipa file"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DShape.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DMaterial.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DMatBlock.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DTevs.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DDrawBuffer.cpp",
                extra_cflags=["-ipa file"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphBase/J3DStruct.cpp",
                extra_cflags=["-ipa file"],
            ),
        ],
    ),
    JSysLib(
        "J3DGraphLoader",
        [
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DMaterialFactory.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DMaterialFactory_v21.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DModelLoader.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DModelLoaderCalcSize.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DJointFactory.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DShapeFactory.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/J3DGraphLoader/J3DAnmLoader.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
        ],
    ),
    JSys_JAudioLib(
        "JAudio2",
        [
            Object(NonMatching, "JSystem/JAudio2/JASCalc.cpp", cflags=cflags_jsys),
            Object(NonMatching, "JSystem/JAudio2/JASTaskThread.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASDvdThread.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASCallback.cpp"),
            Object(
                NonMatching, "JSystem/JAudio2/JASHeapCtrl.cpp", mw_version="GC/3.0a3.2"
            ),
            Object(NonMatching, "JSystem/JAudio2/JASResArcLoader.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASProbe.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASReport.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASCmdStack.cpp"),
            Object(
                NonMatching,
                "JSystem/JAudio2/JASTrack.cpp",
                cflags=[*cflags_jsys_jaudio, "-inline off"],
            ),
            Object(NonMatching, "JSystem/JAudio2/JASTrackPort.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASRegisterParam.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASSeqCtrl.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASSeqParser.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASSeqReader.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASAramStream.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASBank.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASBasicBank.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASVoiceBank.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASBasicInst.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASDrumSet.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASBasicWaveBank.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASSimpleWaveBank.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASInstSense.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASInstRand.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASWSParser.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASBNKParser.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASWaveArcLoader.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASChannel.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASLfo.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASOscillator.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASAiCtrl.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASAudioThread.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASAudioReseter.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASDSPChannel.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASDSPInterface.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASDriverIF.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JASSoundParams.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAIAudible.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAIAudience.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISe.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISeMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISeq.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISeqDataMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISeqMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISound.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISoundChild.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISoundHandles.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISoundInfo.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISoundParams.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAISoundStarter.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAIStream.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAIStreamDataMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAIStreamMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUAudience.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUAudioArcInterpreter.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUAudioArcLoader.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUBankTable.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUInitializer.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSectionHeap.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSeqCollection.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSeqDataBlockMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSoundAnimator.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSoundMgr.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSoundObject.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUSoundTable.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUStdSoundInfo.cpp"),
            Object(NonMatching, "JSystem/JAudio2/JAUStreamFileTable.cpp"),
        ],
    ),
    JSysLib(
        "JGadget",
        [
            Object(
                Matching, "JSystem/JGadget/hashcode.cpp", extra_cflags=["-ipa file"]
            ),
            Object(
                NonMatching, "JSystem/JGadget/linklist.cpp", extra_cflags=["-ipa file"]
            ),
        ],
    ),
    JSysLib(
        "JKernel",
        [
            Object(
                NonMatching, "JSystem/JKernel/JKRHeap.cpp", extra_cflags=["-ipa file"]
            ),
            Object(NonMatching, "JSystem/JKernel/JKRExpHeap.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRSolidHeap.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRUnitHeap.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRDisposer.cpp"),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRThread.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRAram.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRAramHeap.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JKernel/JKRAramBlock.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRAramPiece.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRAramStream.cpp"),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRFileLoader.cpp",
                extra_cflags=["-ipa file"],
            ),
            Object(NonMatching, "JSystem/JKernel/JKRFileFinder.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRArchivePub.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRArchivePri.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRMemArchive.cpp"),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRAramArchive.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JKernel/JKRDvdArchive.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRCompArchive.cpp"),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRDvdFile.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRDvdRipper.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/JKernel/JKRDvdAramRipper.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JKernel/JKRDecomp.cpp"),
        ],
    ),
    JSysLib(
        "JMath",
        [
            Object(NonMatching, "JSystem/JMath/JMath.cpp", extra_cflags=["-opt nocse"]),
            Object(NonMatching, "JSystem/JMath/random.cpp"),
            Object(
                NonMatching,
                "JSystem/JMath/JMATrigonometric.cpp",
                extra_cflags=["-opt nocse"],
            ),
        ],
    ),
    JSys_JParticleLib(
        "JParticle",
        [
            Object(NonMatching, "JSystem/JParticle/JPAResourceManager.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAResource.cpp"),
            Object(
                NonMatching,
                "JSystem/JParticle/JPABaseShape.cpp",
                extra_cflags=["-sym on"],
            ),
            Object(
                NonMatching,
                "JSystem/JParticle/JPAExtraShape.cpp",
                extra_cflags=["-opt nocse"],
            ),
            Object(NonMatching, "JSystem/JParticle/JPAChildShape.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAExTexShape.cpp"),
            Object(
                NonMatching,
                "JSystem/JParticle/JPADynamicsBlock.cpp",
                extra_cflags=["-opt nolifetimes,nocse,noprop", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JParticle/JPAFieldBlock.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAKeyBlock.cpp"),
            Object(
                NonMatching, "JSystem/JParticle/JPATexture.cpp", extra_cflags=["-ipa off"]
            ),
            Object(Matching, "JSystem/JParticle/JPAResourceLoader.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAEmitterManager.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAEmitter.cpp"),
            Object(NonMatching, "JSystem/JParticle/JPAParticle.cpp"),
            Object(
                NonMatching,
                "JSystem/JParticle/JPAMath.cpp",
                extra_cflags=["-opt nolifetimes,nocse"],
            ),
        ],
    ),
    JSysLib(
        "JSupport",
        [
            Object(NonMatching, "JSystem/JSupport/JSUList.cpp"),
            Object(NonMatching, "JSystem/JSupport/JSUInputStream.cpp"),
            Object(NonMatching, "JSystem/JSupport/JSUOutputStream.cpp"),
            Object(NonMatching, "JSystem/JSupport/JSUMemoryStream.cpp"),
            Object(
                NonMatching,
                "JSystem/JSupport/JSUFileStream.cpp",
                extra_cflags=["-ipa file"],
            ),
        ],
    ),
    JSysLib(
        "JUtility",
        [
            Object(
                NonMatching,
                "JSystem/JUtility/JUTTexture.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JUtility/JUTPalette.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTNameTab.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTFont.cpp"),
            Object(
                NonMatching,
                "JSystem/JUtility/JUTException.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JUtility/JUTDirectPrint.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTAssert.cpp"),
            Object(
                NonMatching,
                "JSystem/JUtility/JUTVideo.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JUtility/JUTXfb.cpp"),
            Object(
                NonMatching,
                "JSystem/JUtility/JUTConsole.cpp",
                extra_cflags=["-ipa file", "-sym on"],
            ),
            Object(NonMatching, "JSystem/JUtility/JUTDbPrint.cpp"),
        ],
    ),
    RFLib(
        "RVLFaceLib",
        [
            Object(NonMatching, "RVLFaceLib/RFL_System.c"),
            Object(NonMatching, "RVLFaceLib/RFL_NANDLoader.c"),
            Object(NonMatching, "RVLFaceLib/RFL_NANDAccess.c"),
            Object(NonMatching, "RVLFaceLib/RFL_Model.c"),
            Object(NonMatching, "RVLFaceLib/RFL_MakeTex.c"),
            Object(NonMatching, "RVLFaceLib/RFL_Icon.c"),
            Object(Matching, "RVLFaceLib/RFL_HiddenDatabase.c"),
            Object(NonMatching, "RVLFaceLib/RFL_Database.c"),
            Object(NonMatching, "RVLFaceLib/RFL_Controller.c"),
            Object(NonMatching, "RVLFaceLib/RFL_MiddleDatabase.c"),
            Object(Matching, "RVLFaceLib/RFL_DefaultDatabase.c"),
            Object(NonMatching, "RVLFaceLib/RFL_DataUtility.c"),
            Object(Matching, "RVLFaceLib/RFL_Format.c"),
        ],
    ),
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
        ],
    ),
    GameLib(
        "Map",
        [
            Object(NonMatching, "Game/Map/CollisionCode.cpp"),
            Object(NonMatching, "Game/Map/KCollision.cpp"),
            Object(NonMatching, "Game/Map/RailGraph.cpp"),
            Object(NonMatching, "Game/Map/RailGraphEdge.cpp"),
            Object(NonMatching, "Game/Map/RailGraphIter.cpp"),
            Object(NonMatching, "Game/Map/RailGraphNode.cpp"),
            Object(NonMatching, "Game/Map/RailPart.cpp"),
            Object(NonMatching, "Game/Map/StageSwitch.cpp"),
            Object(NonMatching, "Game/Map/SwitchSynchronizer.cpp"),
            Object(NonMatching, "Game/Map/SwitchWatcher.cpp"),
        ],
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
            Object(NonMatching, "Game/NameObj/NameObjRegister.cpp"),
        ],
    ),
    GameLib(
        "Ride",
        [
            Object(NonMatching, "Game/Ride/TubeSlider.cpp"),
            Object(NonMatching, "Game/Ride/TubeSliderCoinCreator.cpp"),
            Object(NonMatching, "Game/Ride/TubeSliderCrystal.cpp"),
            Object(NonMatching, "Game/Ride/TubeSliderDamageObjCreator.cpp"),
            Object(NonMatching, "Game/Ride/TubeSliderFunction.cpp"),
        ],
    ),
    GameLib(
        "System",
        [
            Object(NonMatching, "Game/System/NerveExecutor.cpp"),
            Object(NonMatching, "Game/System/ResourceInfo.cpp"),
            Object(NonMatching, "Game/System/ScenarioDataParser.cpp"),
        ],
    ),
    GameLib(
        "Util",
        [
            Object(NonMatching, "Game/Util/ActorInitUtil.cpp"),
            Object(NonMatching, "Game/Util/ActorSensorUtil.cpp"),
            Object(NonMatching, "Game/Util/ActorShadowUtil.cpp"),
            Object(NonMatching, "Game/Util/JMapUtil.cpp"),
            Object(NonMatching, "Game/Util/LiveActorUtil.cpp"),
            Object(NonMatching, "Game/Util/MathUtil.cpp"),
            Object(NonMatching, "Game/Util/MtxUtil.cpp"),
        ],
    ),
    RVLLib(
        "gd",
        [
            Object(NonMatching, "RVL_SDK/gd/GDBase.c"),
            Object(NonMatching, "RVL_SDK/gd/GDGeometry.c"),
            Object(NonMatching, "RVL_SDK/gd/GDIndirect.c"),
            Object(NonMatching, "RVL_SDK/gd/GDLight.c"),
            Object(NonMatching, "RVL_SDK/gd/GDPixel.c"),
            Object(NonMatching, "RVL_SDK/gd/GDTev.c"),
            Object(NonMatching, "RVL_SDK/gd/GDTexture.c"),
            Object(NonMatching, "RVL_SDK/gd/GDTransform.c"),
        ],
    ),
    RVLLib(
        "kpad",
        [
            Object(NonMatching, "RVL_SDK/kpad/KPAD.c"),
            Object(NonMatching, "RVL_SDK/kpad/KMPLS.c"),
            Object(NonMatching, "RVL_SDK/kpad/KZMplsTestSub.c"),
        ],
    ),
    RVLLib(
        "tpl",
        [
            Object(NonMatching, "RVL_SDK/tpl/TPL.c"),
        ],
    ),
    RVLLibGC(
        "wenc",
        [
            Object(NonMatching, "RVL_SDK/wenc/wenc.c"),
        ],
        "GC/3.0a5.2",
    ),
    RVLLib(
        "rso",
        [
            Object(NonMatching, "RVL_SDK/rso/RSOLink.c"),
        ],
    ),
    RVLLibGC(
        "net",
        [
            Object(NonMatching, "RVL_SDK/net/nettime.c"),
            Object(NonMatching, "RVL_SDK/net/NETVersion.c"),
            Object(NonMatching, "RVL_SDK/net/netmemcpy.c"),
            Object(NonMatching, "RVL_SDK/net/netmemset.c"),
        ],
        "GC/3.0a5.2",
    ),
    RVLLibGC(
        "nwc24",
        [
            Object(NonMatching, "RVL_SDK/nwc24/NWC24StdAPI.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24FileAPI.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Config.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Utils.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Manage.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24MsgObj.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24MBoxCtrl.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Mime.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Parser.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24MsgCommit.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Schedule.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24DateParser.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24FriendList.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24SecretFList.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24UserId.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Time.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Ipc.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24Download.c"),
            Object(NonMatching, "RVL_SDK/nwc24/NWC24System.c"),
        ],
        "GC/3.0a5.2",
    ),
    RVLLib(
        "vf",
        [
            Object(NonMatching, "RVL_SDK/vf/pf_clib.c"),
            Object(
                NonMatching,
                "RVL_SDK/vf/pf_code.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/vf/pf_service.c"),
            Object(
                NonMatching,
                "RVL_SDK/vf/pf_str.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/vf/pf_w_clib.c"),
            Object(
                NonMatching,
                "RVL_SDK/vf/pf_driver.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/vf/pdm_bpb.c"),
            Object(NonMatching, "RVL_SDK/vf/pdm_disk.c"),
            Object(NonMatching, "RVL_SDK/vf/pdm_partition.c"),
            Object(NonMatching, "RVL_SDK/vf/pdm_mbr.c"),
            Object(NonMatching, "RVL_SDK/vf/pdm_dskmng.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_cache.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_cluster.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_dir.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_entry.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_entry_iterator.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fat.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fat12.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fat16.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fat32.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fatfs.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_file.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_path.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_sector.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_volume.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_cp932.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_api_util.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_attach.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_detach.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_errnum.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fclose.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_finfo.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fopen.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fread.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fseek.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_fwrite.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_getdev.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_init_prfile2.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_remove.c"),
            Object(NonMatching, "RVL_SDK/vf/pf_unmount.c"),
            Object(
                NonMatching,
                "RVL_SDK/vf/pf_filelock.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/vf/pf_system.c"),
            Object(
                NonMatching,
                "RVL_SDK/vf/d_vf.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/vf/d_vf_sys.c"),
            Object(NonMatching, "RVL_SDK/vf/d_hash.c"),
            Object(NonMatching, "RVL_SDK/vf/d_time.c"),
            Object(NonMatching, "RVL_SDK/vf/d_common.c"),
            Object(NonMatching, "RVL_SDK/vf/nand_drv.c"),
        ],
    ),
    RVLLibGC(
        "aralt",
        [
            Object(NonMatching, "RVL_SDK/aralt/aralt.c", extra_cflags=["-O4,s"]),
        ],
    ),
    RVLLib(
        "base",
        [
            Object(NonMatching, "RVL_SDK/base/PPCArch.c"),
        ],
    ),
    RVLLib(
        "os",
        [
            Object(NonMatching, "RVL_SDK/os/OS.c"),
            Object(NonMatching, "RVL_SDK/os/OSAlarm.c"),
            Object(NonMatching, "RVL_SDK/os/OSAlloc.c"),
            Object(NonMatching, "RVL_SDK/os/OSArena.c"),
            Object(NonMatching, "RVL_SDK/os/OSAudioSystem.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/OSCache.c",
                mw_version="GC/3.0a5.2",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/os/OSContext.c"),
            Object(NonMatching, "RVL_SDK/os/OSError.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/OSExec.c",
                extra_cflags=["-opt nolifetimes,noloop"],
            ),
            Object(NonMatching, "RVL_SDK/os/OSFatal.c"),
            Object(NonMatching, "RVL_SDK/os/OSFont.c"),
            Object(NonMatching, "RVL_SDK/os/OSInterrupt.c"),
            Object(NonMatching, "RVL_SDK/os/OSLink.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/OSMessage.c",
                mw_version="GC/3.0a5.2",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/os/OSMemory.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/OSMutex.c",
                mw_version="GC/3.0a5.2",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/os/OSReboot.c"),
            Object(NonMatching, "RVL_SDK/os/OSReset.c"),
            Object(NonMatching, "RVL_SDK/os/OSRtc.c"),
            Object(NonMatching, "RVL_SDK/os/OSSync.c"),
            Object(NonMatching, "RVL_SDK/os/OSThread.c"),
            Object(NonMatching, "RVL_SDK/os/OSTime.c"),
            Object(NonMatching, "RVL_SDK/os/OSUtf.c"),
            Object(NonMatching, "RVL_SDK/os/OSIpc.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/OSStateTM.c",
                extra_cflags=[
                    "-flag no-opt_generateconditionalassignments",
                    "-flag no-opt_rebuildconditionals",
                ],
            ),
            Object(NonMatching, "RVL_SDK/os/OSPlayRecord.c"),
            Object(NonMatching, "RVL_SDK/os/OSStateFlags.c"),
            Object(NonMatching, "RVL_SDK/os/OSNet.c"),
            Object(NonMatching, "RVL_SDK/os/OSNandbootInfo.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/OSPlayTime.c",
                mw_version="GC/3.0a5.2",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/os/OSCrc.c"),
            Object(NonMatching, "RVL_SDK/os/OSLaunch.c"),
            Object(NonMatching, "RVL_SDK/os/__ppc_eabi_init.c"),
            Object(
                NonMatching,
                "RVL_SDK/os/init/__start.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(
                NonMatching,
                "RVL_SDK/os/init/__ppc_eabi_init.cpp",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
        ],
    ),
    RVLLib(
        "exi",
        [
            Object(NonMatching, "RVL_SDK/exi/EXIBios.c"),
            Object(NonMatching, "RVL_SDK/exi/EXIUart.c", cflags=cflags_sdk_ipa),
            Object(NonMatching, "RVL_SDK/exi/EXICommon.c", cflags=cflags_sdk_ipa),
        ],
        cflags_sdk_exi,
    ),
    RVLLib(
        "si",
        [
            Object(NonMatching, "RVL_SDK/si/SIBios.c"),
            Object(NonMatching, "RVL_SDK/si/SISamplingRate.c"),
        ],
    ),
    RVLLib(
        "vi",
        [
            Object(NonMatching, "RVL_SDK/vi/vi.c"),
            Object(NonMatching, "RVL_SDK/vi/i2c.c"),
            Object(NonMatching, "RVL_SDK/vi/vi3in1.c"),
        ],
    ),
    RVLLib(
        "mtx",
        [
            Object(NonMatching, "RVL_SDK/mtx/mtx.c"),
            Object(NonMatching, "RVL_SDK/mtx/mtxvec.c"),
            Object(NonMatching, "RVL_SDK/mtx/mtx44.c"),
            Object(
                NonMatching,
                "RVL_SDK/mtx/vec.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/mtx/quat.c"),
        ],
    ),
    RVLLib(
        "gx",
        [
            Object(NonMatching, "RVL_SDK/gx/GXInit.c"),
            Object(NonMatching, "RVL_SDK/gx/GXFifo.c"),
            Object(NonMatching, "RVL_SDK/gx/GXAttr.c"),
            Object(NonMatching, "RVL_SDK/gx/GXMisc.c"),
            Object(NonMatching, "RVL_SDK/gx/GXGeometry.c"),
            Object(NonMatching, "RVL_SDK/gx/GXFrameBuf.c"),
            Object(NonMatching, "RVL_SDK/gx/GXLight.c"),
            Object(NonMatching, "RVL_SDK/gx/GXTexture.c"),
            Object(NonMatching, "RVL_SDK/gx/GXBump.c"),
            Object(NonMatching, "RVL_SDK/gx/GXTev.c"),
            Object(NonMatching, "RVL_SDK/gx/GXPixel.c"),
            Object(NonMatching, "RVL_SDK/gx/GXDisplayList.c"),
            Object(NonMatching, "RVL_SDK/gx/GXTransform.c"),
            Object(NonMatching, "RVL_SDK/gx/GXPerf.c"),
        ],
    ),
    RVLLib(
        "dvd",
        [
            Object(
                NonMatching,
                "RVL_SDK/dvd/dvdfs.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/dvd/dvd.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdqueue.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvderror.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdidutils.c"),
            Object(
                NonMatching,
                "RVL_SDK/dvd/dvdFatal.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/dvd/dvdDeviceError.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvd_broadway.c"),
        ],
    ),
    RVLLibGC(
        "ai",
        [
            Object(NonMatching, "RVL_SDK/ai/ai.c"),
        ],
    ),
    RVLLib(
        "ax",
        [
            Object(NonMatching, "RVL_SDK/ax/AXAlloc.c"),
            Object(NonMatching, "RVL_SDK/ax/AXAux.c"),
            Object(NonMatching, "RVL_SDK/ax/AXCL.c"),
            Object(NonMatching, "RVL_SDK/ax/AXVPB.c"),
        ],
    ),
    RVLLib(
        "axfx",
        [
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbHi.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbHiExp.c"),
            Object(
                NonMatching,
                "RVL_SDK/axfx/AXFXHooks.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
        ],
    ),
    RVLLib(
        "mem",
        [
            Object(NonMatching, "RVL_SDK/mem/mem_heapCommon.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_expHeap.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_allocator.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_list.c"),
        ],
    ),
    RVLLib(
        "dsp",
        [
            Object(NonMatching, "RVL_SDK/dsp/dsp.c"),
            Object(NonMatching, "RVL_SDK/dsp/dsp_debug.c"),
            Object(
                NonMatching,
                "RVL_SDK/dsp/dsp_task.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
        ],
    ),
    RVLLib(
        "nand",
        [
            Object(NonMatching, "RVL_SDK/nand/nand.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDOpenClose.c"),
            Object(
                NonMatching,
                "RVL_SDK/nand/NANDCore.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/nand/NANDCheck.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDLogging.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDErrorMessage.c"),
        ],
    ),
    RVLLib(
        "sc",
        [
            Object(NonMatching, "RVL_SDK/sc/scsystem.c"),
            Object(
                NonMatching,
                "RVL_SDK/sc/scapi.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/sc/scapi_prdinfo.c"),
        ],
    ),
    RVLLib(
        "arc",
        [
            Object(NonMatching, "RVL_SDK/arc/arc.c"),
        ],
    ),
    RVLLib(
        "esp",
        [
            Object(NonMatching, "RVL_SDK/esp/esp.c"),
        ],
    ),
    RVLLib(
        "ipc",
        [
            Object(
                NonMatching,
                "RVL_SDK/ipc/ipcMain.c",
                mw_version="GC/3.0a3",
                cflags=cflags_sdk_gc,
            ),
            Object(NonMatching, "RVL_SDK/ipc/ipcclt.c"),
            Object(NonMatching, "RVL_SDK/ipc/memory.c"),
            Object(NonMatching, "RVL_SDK/ipc/ipcProfile.c"),
        ],
    ),
    RVLLib(
        "fs",
        [
            Object(NonMatching, "RVL_SDK/fs/fs.c"),
        ],
    ),
    RVLLib(
        "pad",
        [
            Object(NonMatching, "RVL_SDK/pad/Pad.c"),
        ],
    ),
    RVLLib(
        "wpad",
        [
            Object(NonMatching, "RVL_SDK/wpad/WPAD.c", extra_cflags=["-fp off"]),
            Object(NonMatching, "RVL_SDK/wpad/WPADHIDParser.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPADEncrypt.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPADMem.c"),
            Object(NonMatching, "RVL_SDK/wpad/lint.c"),
        ],
    ),
    RVLLib(
        "wud",
        [
            Object(NonMatching, "RVL_SDK/wud/WUD.c"),
            Object(NonMatching, "RVL_SDK/wud/WUDHidHost.c"),
        ],
    ),
    RVLLib(
        "euart",
        [
            Object(NonMatching, "RVL_SDK/euart/euart.c"),
        ],
    ),
    RVLLib(
        "usb",
        [
            Object(NonMatching, "RVL_SDK/usb/usb.c"),
        ],
    ),
    RVLLibGC(
        "bte",
        [
            Object(
                NonMatching,
                "RVL_SDK/bte/gki_buffer.c",
                mw_version="Wii/1.0",
                cflags=cflags_sdk_ipa,
            ),
            Object(
                NonMatching,
                "RVL_SDK/bte/gki_time.c",
                mw_version="Wii/1.0",
                cflags=cflags_sdk_ipa,
            ),
            Object(
                NonMatching,
                "RVL_SDK/bte/gki_ppc.c",
                mw_version="Wii/1.0",
                cflags=cflags_sdk_ipa,
            ),
            Object(
                NonMatching,
                "RVL_SDK/bte/hcisu_h2.c",
                mw_version="Wii/1.0",
                cflags=cflags_sdk_ipa,
            ),
            Object(NonMatching, "RVL_SDK/bte/uusb_ppc.c", mw_version="GC/3.0a5.2"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_cfg.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_cfg.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_sys_cfg.c"),
            Object(NonMatching, "RVL_SDK/bte/bte_hcisu.c"),
            Object(NonMatching, "RVL_SDK/bte/bte_init.c"),
            Object(
                NonMatching,
                "RVL_SDK/bte/bte_logmsg.c",
                mw_version="Wii/1.0",
                cflags=cflags_sdk_ipa,
            ),
            Object(NonMatching, "RVL_SDK/bte/bte_main.c"),
            Object(NonMatching, "RVL_SDK/bte/btu_task1.c"),
            Object(NonMatching, "RVL_SDK/bte/bd.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_sys_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_sys_main.c"),
            Object(NonMatching, "RVL_SDK/bte/ptim.c"),
            Object(NonMatching, "RVL_SDK/bte/utl.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_act.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_api.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_main.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_pm.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_act.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_api.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_main.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_acl.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_dev.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_devctl.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_discovery.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_inq.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_main.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_pm.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_sco.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_sec.c"),
            Object(NonMatching, "RVL_SDK/bte/btu_hcif.c"),
            Object(NonMatching, "RVL_SDK/bte/btu_init.c"),
            Object(NonMatching, "RVL_SDK/bte/wbt_ext.c"),
            Object(NonMatching, "RVL_SDK/bte/gap_api.c"),
            Object(NonMatching, "RVL_SDK/bte/gap_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/gap_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/hcicmds.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_api.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_mgmt.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_pm.c"),
            Object(NonMatching, "RVL_SDK/bte/hidh_api.c"),
            Object(NonMatching, "RVL_SDK/bte/hidh_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_api.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_csm.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_link.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_main.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/port_api.c"),
            Object(NonMatching, "RVL_SDK/bte/port_rfc.c"),
            Object(NonMatching, "RVL_SDK/bte/port_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_l2cap_if.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_mx_fsm.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_port_fsm.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_port_if.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_ts_frames.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_api.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_db.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_discovery.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_main.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_server.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_utils.c"),
        ],
    ),
    NWLib(
        "libnw4r_ut",
        [
            Object(NonMatching, "nw4r/ut/ut_LinkList.cpp"),
            Object(Matching, "nw4r/ut/ut_binaryFileFormat.cpp"),
            Object(Matching, "nw4r/ut/ut_CharStrmReader.cpp"),
            Object(NonMatching, "nw4r/ut/ut_TagProcessorBase.cpp"),
            Object(NonMatching, "nw4r/ut/ut_Font.cpp"),
            Object(NonMatching, "nw4r/ut/ut_ResFontBase.cpp"),
            Object(NonMatching, "nw4r/ut/ut_ResFont.cpp"),
            Object(NonMatching, "nw4r/ut/ut_CharWriter.cpp"),
            Object(NonMatching, "nw4r/ut/ut_TextWriterBase.cpp"),
        ],
    ),
    NWLib(
        "libnw4r_db",
        [
            Object(NonMatching, "nw4r/db/db_console.cpp"),
            Object(NonMatching, "nw4r/db/db_assert.cpp"),
        ],
    ),
    NWLib(
        "libnw4r_math",
        [
            Object(NonMatching, "nw4r/math/math_triangular.cpp"),
            Object(Matching, "nw4r/math/math_types.cpp"),
        ],
    ),
    NWLib(
        "libnw4r_lyt",
        [
            Object(NonMatching, "nw4r/lyt/lyt_init.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_pane.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_group.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_layout.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_picture.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_textBox.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_window.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_bounding.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_material.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_texMap.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_drawInfo.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_animation.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_resourceAccessor.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_common.cpp"),
        ],
    ),
    MSLLib(
        "MSL_C",
        [
            Object(Matching, "MSL_C/alloc.c"),
            Object(Matching, "MSL_C/errno.c"),
            Object(Matching, "MSL_C/ansi_files.c"),
            Object(Matching, "MSL_C/ansi_fp.c"),
            Object(Matching, "MSL_C/arith.c"),
            Object(Matching, "MSL_C/ctype.c"),
            Object(Matching, "MSL_C/locale.c"),
            Object(Matching, "MSL_C/buffer_io.c"),
            Object(Matching, "MSL_C/direct_io.c"),
            Object(Matching, "MSL_C/file_io.c"),
            Object(Matching, "MSL_C/FILE_POS.c"),
            Object(Matching, "MSL_C/mbstring.c"),
            Object(Matching, "MSL_C/mem.c"),
            Object(Matching, "MSL_C/mem_funcs.c"),
            Object(Matching, "MSL_C/math_api.c"),
            Object(Matching, "MSL_C/misc_io.c"),
            Object(Matching, "MSL_C/printf.c"),
            Object(Matching, "MSL_C/float.c"),
            Object(Matching, "MSL_C/scanf.c"),
            Object(Matching, "MSL_C/signal.c"),
            Object(Matching, "MSL_C/string.c"),
            Object(Matching, "MSL_C/strtold.c"),
            Object(Matching, "MSL_C/wctype.c"),
            Object(Matching, "MSL_C/strtoul.c"),
            Object(Matching, "MSL_C/wcstoul.c"),
            Object(Matching, "MSL_C/wmem.c"),
            Object(Matching, "MSL_C/wprintf.c"),
            Object(Matching, "MSL_C/wscanf.c"),
            Object(Matching, "MSL_C/wstring.c"),
            Object(Matching, "MSL_C/wchar_io.c"),
            Object(Matching, "MSL_C/uart_console_io_gcn.c"),
            Object(Matching, "MSL_C/abort_exit_ppc_eabi.c"),
            Object(Matching, "MSL_C/secure_error.c"),
            Object(Matching, "MSL_C/math_sun.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_acos.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_asin.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_atan2.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_fmod.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_log.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_log10.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_pow.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_rem_pio2.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_cos.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_rem_pio2.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_sin.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/k_tan.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_atan.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ceil.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_copysign.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_cos.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_floor.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_frexp.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ldexp.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_sin.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/s_tan.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_acos.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_asin.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_atan2.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_fmod.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_log10.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_pow.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/e_sqrt.c"),
            Object(Matching, "MSL_C/PPC_EABI/SRC/math_ppc.c"),
            Object(Matching, "MSL_C/MSL_Common_Embedded/Math/Double_precision/w_sqrt.c"),
            Object(Matching, "MSL_C/extras.c"),
        ],
    ),
    TRKLib(
        "MetroTRK",
        [
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Processor/ppc/Generic/exception.s"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Processor/ppc/Export/targsupp.s"),
            Object(Matching, "MetroTRK/gamedev/cust_connection/cc/exi2/GCN/EXI2_GDEV_GCN/main.c"),
            Object(Matching, "MetroTRK/gamedev/cust_connection/utils/gc/MWCriticalSection_gc.c"),
            Object(Matching, "MetroTRK/gamedev/cust_connection/utils/common/CircleBuffer.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Processor/ppc/Generic/flush_cache.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/main_TRK.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/mainloop.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/mem_TRK.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/dispatch.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Os/dolphin/dolphin_trk.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Os/dolphin/dolphin_trk_glue.c", extra_cflags=["-str pool"]),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/notify.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/nubevent.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/nubinit.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/serpoll.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/string_TRK.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/support.c", extra_cflags=["-str pool"]),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Os/dolphin/targcont.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Processor/ppc/Generic/mpc_7xx_603e.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/msg.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/msgbuf.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Portable/msghndlr.c", extra_cflags=["-str pool"]),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Export/mslsupp.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Processor/ppc/Generic/targimpl.c"),
            Object(Matching, "MetroTRK/debugger/embedded/MetroTRK/Os/dolphin/target_options.c"),
        ],
    ),
]

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("nw4r", "NintendoWare Code"),
    ProgressCategory("jsys", "JSystem"),
    ProgressCategory("rfl", "RVLFaceLib"),
    ProgressCategory("msl", "MSL_C Code"),
    ProgressCategory("trk", "MetroTRK Code"),
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
