#pragma once
#ifndef TRICK_H
#define TRICK_H
#include<Windows.h>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<mmsystem.h>
#include<mciapi.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
using namespace cv;
POINT target[10], P;
HHOOK mouseHook;
int question, angle, num, speed1, speed2;
char answer[] = {'A','C','B','C','A','B','B'};
String Name[] = { "LZY0","LZY1","LZY2","LZY3","LZY4","LZY5","LZY6","LZY7","LZY8","LZY9" };
LPCWSTR name[] = { L"LZY0",L"LZY1",L"LZY2",L"LZY3",L"LZY4",L"LZY5",L"LZY6",L"LZY7",L"LZY8",L"LZY9" };
Mat img;
void SetImage(int i) {
    img = imread("LZY.png");
    namedWindow(Name[i], WINDOW_AUTOSIZE);
    return;
}
void PlayAudio() {
    mciSendString(L"open \"NGM.mp3\" type MPEGVideo alias MP3_Device", NULL, 0, NULL);
    mciSendString(L"play MP3_Device from 0", NULL, 0, NULL);
    return;
}
bool inA(POINT p) {

    return false;
}
bool inB(POINT p) {

    return false;
}
bool inC(POINT p) {

    return false;
}
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) {
        return CallNextHookEx(mouseHook, nCode, wParam, lParam);
    }
    if (wParam == WM_LBUTTONDOWN) {
        POINT pt;
        GetCursorPos(&pt);
        for (int i = 0; i < num; i++) {
            HWND hwnd = FindWindow(NULL, name[i]);
            RECT rc;
            GetWindowRect(hwnd, &rc);
            if (PtInRect(&rc, pt)) {
                PlayAudio();
            }
        }

    }
    return 0;
}
void RotateImage() {
    Point2f center(img.cols / 2.0, img.rows / 2.0);
    double scale = 1.0;
    Mat rot_mat = getRotationMatrix2D(center, angle, scale);
    Mat rotated_img;
    warpAffine(img, rotated_img, rot_mat, img.size());
    for (int i = 0; i < num; i++) {
        imshow(Name[i], rotated_img);
    }
    int key = waitKey(30);
    angle = angle + 3 * speed2;
    if (angle >= 360) {
        angle = -360;
    }
    return;
}
void GenerateRandomTarget(int i) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    target[i].x = rand() % (screenWidth - 200);
    target[i].y = rand() % (screenHeight - 100);
    return;
}
int CalculateDistance(int time, int speed) {
    double t = time / 1000.0;
    double f = t * t / (t * t + (1 - t) * (1 - t));
    int distance = (int)(f * speed);
    return distance;
}
void MoveWindowToTarget() {
    int centerX[10], centerY[10], dx[10], dy[10];
    for (int i = 0; i < num; i++) {
        GenerateRandomTarget(i);
        RECT rect;
        GetWindowRect(FindWindow(NULL, name[i]), &rect);
        centerX[i] = (rect.left + rect.right) / 2;
        centerY[i] = (rect.top + rect.bottom) / 2;
        dx[i] = target[i].x - centerX[i];
        dy[i] = target[i].y - centerY[i];
    }
    //if (abs(dx) < 10 && abs(dy) < 10) return;
    UINT_PTR timerId = SetTimer(NULL, 0, 50, NULL);
    DWORD startTime = GetTickCount(), endTime = startTime + 2000 - 180 * speed1;
    while (true) {
        DWORD currentTime = GetTickCount();
        if (currentTime > endTime) {
            KillTimer(NULL, timerId);
            break;
        }
        int elapsedTime = currentTime - startTime;
        for (int i = 0; i < num; i++) {
            int moveX = CalculateDistance(elapsedTime, dx[i]);
            int moveY = CalculateDistance(elapsedTime, dy[i]);
            int newX = centerX[i] + moveX - 200;
            int newY = centerY[i] + moveY - 100;
            int newWidth = 200, newHeight = 236;
            MoveWindow(FindWindow(NULL, name[i]), newX, newY, newWidth, newHeight, TRUE);
            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        RotateImage();
    }
   // MoveWindow(FindWindow(NULL, L"LZY"), target.x - 100, target.y - 50, rect.right - rect.left, 236, TRUE);
    return;
}
void SetClipBoard(string TempBin) {
    HGLOBAL hMemBin = NULL;
    PCHAR  LockBin = NULL;
    OpenClipboard(NULL);
    EmptyClipboard();
    hMemBin = GlobalAlloc(GMEM_MOVEABLE, TempBin.size() + 1);
    LockBin = (PCHAR)GlobalLock(hMemBin);
    RtlMoveMemory(LockBin, TempBin.c_str(), TempBin.size() + 1);
    GlobalUnlock(hMemBin);
    LockBin = NULL;
    SetClipboardData(CF_TEXT, hMemBin);
    CloseClipboard();
    return;
}
bool Question() {
    String Filename = "Q" + char(question + 48);
    Mat Qmg = imread(Filename, WINDOW_AUTOSIZE);

    return true;
}
#endif