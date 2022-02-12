#ifndef _MYMENU_
#define _MYMENU_
#include "public.h"
#include "Timer.h"
#include "huffman.h"
#include "FileIO.h"

void Start();   // 프로그램 시작 함수
void PrintEncodingMenu(Huffman*);   // 압축 수행 메뉴 출력
void PrintDecodingMenu(Huffman*);   // 압축 해제 수행 메뉴 출력

#endif