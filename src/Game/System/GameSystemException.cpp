#include "Game/System/GameSystemException.hpp"
#include "Game/System/GameSystem.hpp"
#include "Game/System/GameSystemObjHolder.hpp"
#include "Game/Util/GamePadUtil.hpp"
#include "Game/Util/SingletonHolder.hpp"
#include <JSystem/JUtility/JUTAssert.hpp>
#include <JSystem/JUtility/JUTConsole.hpp>
#include <JSystem/JUtility/JUTDirectPrint.hpp>
#include <JSystem/JUtility/JUTException.hpp>
#include <JSystem/JUtility/JUTVideo.hpp>

extern "C" {
void fn_805B48F0(u32);
}

void* GameSystemException::sMapFileUsingBuffer;

namespace {
    bool isBootWPAD() {
        GameSystemObjHolder* objHolder = SingletonHolder< GameSystem >::get()->mObjHolder;
        return objHolder != nullptr && objHolder->mWPadHolder != nullptr;
    }

    const u32 cDispExceptionCommand[] = {
        0x0200,  // B Button
        0x0100,  // A Button
        0x0004,  // +Control Pad ↓
        0x0001,  // +Control Pad ←
        0x0008,  // +Control Pad ↑
        0x0002,  // +Control Pad →
        0x0010,  // 1 Button + 2 Button
        0x0000,
    };
};  // namespace

void GameSystemException::init() {
    JUTDirectPrint* directPrint = JUTDirectPrint::start();

    JUTAssertion::create();
    JUTAssertion::changeDisplayTime(600);
    JUTAssertion::changeDevice(3);
    JUTConsoleManager::createManager(nullptr);
    JUTException::create(directPrint);
    JUTException::createConsole(new u8[0x24FC], 0x24FC);
    JUTException::setPreUserCallback(GameSystemException::handleException);
    JUTException::sErrorManager->mPrintWaitTime1 = 0;
    JUTException::sErrorManager->mPrintWaitTime0 = 0;

    JUTConsole* console = JUTException::getConsole();
    console->mPositionX = 0xF;
    console->mPositionY = 0x30;
    console = JUTException::getConsole();
    console->mHeight = 0x16;

    if (console->mHeight > console->mMaxLines) {
        console->mHeight = console->mMaxLines;
    }

    GameSystemException::sMapFileUsingBuffer = new u8[0x10];
}

void GameSystemException::handleException(OSError error, OSContext* pContext, u32 dsisr, u32 dar) {
    fn_805B48F0(0x22B);

    if (JUTVideo::getManager() == nullptr) {
        JUTException::sConsole->mOutput = 2;
        JUTException::sConsole->mVisible = false;
        JUTAssertion::setVisible(false);
    }

    VIFlush();
    JUTAssertion::flushMessage();

    if (::isBootWPAD()) {
        for (s32 chan = WPAD_CHAN0; chan < WPAD_CHAN0 + MR::getWPadMaxCount(); chan++) {
            WPADControlMotor(chan, WPAD_MOTOR_STOP);
        }

        JUTException* exception = JUTException::sErrorManager;
        exception->mGamePad = reinterpret_cast< JUTGamePad* >(0xFFFFFFFF);
        exception->mGamePadPort = JUTGamePad::Port_Unknown;
    }

    AIRegisterDMACallback(nullptr);

    if (::isBootWPAD()) {
        s32 padCommandSuccessCounter = 0;
        u32 padCommandTrigger = 0;
        u32 padCommandHold = 0;

        while (::cDispExceptionCommand[padCommandSuccessCounter]) {
            JUTException::waitTime(50);
            JUTException::sErrorManager->readPad(&padCommandTrigger, &padCommandHold);

            if (padCommandTrigger == 0) {
                continue;
            }

            if ((::cDispExceptionCommand[padCommandSuccessCounter] & padCommandTrigger) == ::cDispExceptionCommand[padCommandSuccessCounter]) {
                padCommandSuccessCounter++;
            } else {
                padCommandSuccessCounter = 0;
            }
        }
    }
}
