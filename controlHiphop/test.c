#include <Windows.h> 
#include <Winuser.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define MAX_COMMAND_COUNT 100
#define MAX_COMMAND_SIZE 100
#define SLEEP_TIME 100
char command[MAX_COMMAND_COUNT][MAX_COMMAND_SIZE] = {0};
int  delay[MAX_COMMAND_COUNT] = {0};
HWND text_hand[11] = {0};
HWND desc_hand[11] = {0};
HWND send_hand[11] = {0};
/*
void snapwin_2_clipboard() 
{ 
  keybd_event(VK_LWIN,0,0 , 0); //Alt Press
  keybd_event('M',0,0 , 0); // Tab Press
  keybd_event('M',0, KEYEVENTF_KEYUP,0); // Tab Release
  keybd_event(VK_LWIN,0,KEYEVENTF_KEYUP,0); // Alt Release
} 
BOOL enumChild(HWND handler, LPARAM parm){
   LPTSTR str[20], str1[20];
   GetClassName(handler, str, sizeof(str));
   GetWindowText(handler, str1, sizeof(str1));
   if(stricmp((char*)str, "combobox")==0){
     int count = SendMessage(handler, CB_GETCOUNT, 0, 0);
     if(count != 15){
       return TRUE;
     }
     SendMessage(handler, CB_SETCURSEL , 13, 0);
   }
   else if(stricmp((char*)str, "static") == 0 && stricmp(":w")){

   }
   if(!stricmp((char*)str1, "DlgRawCmd")){
     int id = GetDlgCtrlID(handler);
     int parent = GetWindowLong(handler, GWL_HWNDPARENT);
     WPARAM wParam;
     LPARAM lParam = handler;
     wParam = (id | (BN_CLICKED << 8));
     SendMessage(parent, WM_COMMAND, wParam, lParam);
     printf("%d %d %d\n", id, BN_CLICKED, wParam);
     printf("%d %d\n",LOWORD(wParam) , HIWORD(wParam));
     if(BN_CLICKED == HIWORD(wParam) && id == LOWORD(wParam)){
        printf("%x %x %x\n", handler, id, parent);
     }

   }
   return TRUE;
} */
BOOL enumChild(HWND handler, LPARAM parm){
    static int count = 0;
    static BOOL isFound = FALSE;
    char winText[20];
    GetWindowText(handler, winText, sizeof(winText));
    if(!stricmp((char*)winText, "description")){
        isFound = TRUE;
        count = 0;
        return TRUE;
    }
    if(isFound){
        int controlId = GetDlgCtrlID(handler);
        if(count % 3 == 0){
            text_hand[count / 3] = handler;
        }
        else if((count - 1)% 3 == 0){
            send_hand[(count - 1) / 3] = handler;
        }
        else{
            desc_hand[(count - 2) / 3] = handler;
        }
        count++;
    }
    if(count == 30){
        isFound = FALSE;
        return FALSE;
    }
    return TRUE;
}
BOOL parseTextCommand(int* totalCount, char* file){
    FILE* fp = fopen(file, "r");
    int cot = 0;
    if(fp == NULL){
        printf("file open failed...\n");
        return FALSE;
    }
    while(cot < MAX_COMMAND_COUNT && fscanf(fp, "%s %d", command[cot], &delay[cot++]) != EOF){
    }
    if(cot == MAX_COMMAND_COUNT)
        *totalCount = cot;
    else
        *totalCount = cot - 1;
    return TRUE;
}
int main(int argc, char** argv) 
{
    HWND handler = NULL;
    int totalCount = 0;
    char ch = 0;
    int now_time = 0;
    char targetFile[30];
    int i = 0, j = 0;
    char result[100];

    if(argc != 2){
        printf("we need one argument, the aim file...\n");
        return 0;
    }

    memset(targetFile, 0, sizeof(targetFile));
    strncpy(targetFile, argv[1], sizeof(targetFile)-1);

    if(!parseTextCommand(&totalCount, targetFile))
        return 0;

    if(totalCount == MAX_COMMAND_COUNT)
        printf("too many commands.... just can input top 100 command.");

    handler = FindWindowEx(NULL,NULL, NULL, "wxHiphop");
    if(handler != NULL){
        if(IsIconic(handler)){
            ShowWindow(handler, SW_RESTORE);
        }
        else{
            ShowWindow(handler, SW_SHOWNORMAL);
        }
        BringWindowToTop(handler);
        EnumChildWindows(handler, (WNDENUMPROC)enumChild, NULL);
    }
    else{
        printf("not found wxHiphop window, please open it first.\n");
        return 0;
    }

    /*while(ch != 'n' && ch != 'N'){
      int i = 0;
      char tmp_ch[20];
      for(; i < 10; i++){
      char buf[10];
      SendMessage(text_hand[i], WM_SETTEXT, 0, command[now_time * 10 + i]);
      }

      now_time++;
      totalCount -= 10;

      if(totalCount <= 0)
      break;
      printf("left %d commands, continue?", totalCount);
      scanf("%s", tmp_ch);
      ch = tmp_ch[0];
      }*/
    for(j = 0; j < 10; j++){
        SendMessage(text_hand[j], WM_SETTEXT, 0, "");
        SendMessage(desc_hand[j], WM_SETTEXT, 0, "");
    }
    for(i = 0; i < totalCount; i++){
        int command_set = i % 10;
        SendMessage(text_hand[command_set], WM_SETTEXT, 0, command[i]);
        SendMessage(send_hand[command_set], WM_LBUTTONDOWN, MK_LBUTTON, 0);
        SendMessage(send_hand[command_set], WM_LBUTTONUP, MK_LBUTTON, 0);
        SendMessage(desc_hand[command_set], WM_SETTEXT, 0, "OK");

        if(i != totalCount - 1)
            Sleep(SLEEP_TIME + delay[i+1]);

        if(command_set == 9 || i == totalCount - 1){
            for(j = 0; j < 10; j++){
                SendMessage(text_hand[j], WM_SETTEXT, 0, "");
                SendMessage(desc_hand[j], WM_SETTEXT, 0, "");
            }
        }
    }
    sprintf(result, "Total %d commands have inputed ok...", totalCount );
    SendMessage(desc_hand[9], WM_SETTEXT, 0, result);
    return 0;
} 
