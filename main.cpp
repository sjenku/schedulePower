#include <iostream>
#include <windows.h>
#include "resource.h"
#include <commctrl.h>
#include <sstream>
#include <string>
#include "DataSchedule.hpp"






/*-------------------------------Declaretions---------------------------------*/
VOID CreateMainWindow(HINSTANCE);
VOID WhileLoop(VOID);
VOID CreateMainControllers(HWND hMainWnd);
VOID InitDialogWithStrings(HWND hDlg);
VOID InitDialogWithHours(HWND hDlg,int idCB);
VOID InitDialogWithMinutes(HWND hDlg,int idCB);
BOOL CALLBACK StuDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK TimeDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
VOID AddItemToListBox(HWND hwnd,int IDListBox,char* str,UINT index);
char* PullTextFromTextField(HWND hwnd,UINT idControl);
void generateButton();

/*-------------------------------Global Var---------------------------------*/
HWND g_hMainWnd = NULL,g_hAddBt = NULL,g_hRemoveBt = NULL,g_hGenerateBt = NULL,g_hListBox,g_StuDlg,g_TimeDlg;
LPCWSTR g_mainClassName = L"MyMainWindowClass";
HINSTANCE g_inst;
char* days[] = {
    "ראשון","שני","שלישי","רביעי","חמישי","שישי","שבת"
};
/*-------------------------------Main Function---------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

 CreateMainWindow(hInstance);
 WhileLoop();

 return 0;
}


/*-------------------------------Functions---------------------------------*/
LRESULT CALLBACK WinProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg)
     {
        case WM_COMMAND:
             switch(LOWORD(wp))
                {
                    case ID_BT_ADD:
                            {
                                int ret = DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_STU_DLG),hwnd,StuDlgProc);
                                if (ret == IDOK) MessageBox(hwnd,"WIth IDOK","",MB_OK);
                                else if (ret == IDCANCEL) MessageBeep(MB_OK);
                            }
                         break;
                }
             break;
        case WM_CREATE:
            CreateMainControllers(hwnd);
             break;
        case WM_CLOSE:
               DestroyWindow(hwnd);
             break;
        case WM_DESTROY:
               PostQuitMessage(0);
             break;
        default:
             return DefWindowProc(hwnd,msg,wp,lp);
     }
     return 0;
}

VOID CreateMainWindow(HINSTANCE hInstance)
{


    WNDCLASSW wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = HBRUSH(COLOR_WINDOW + 6);
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WinProc;
    wc.lpszClassName = g_mainClassName;
    wc.lpszMenuName = NULL;
    wc.style = 0;
     RegisterClassW(&wc);

    g_hMainWnd = CreateWindowW(g_mainClassName,L"Hello",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,248,248,NULL,NULL,GetModuleHandle(NULL),NULL);
     if (g_hMainWnd != NULL)
     {
         g_inst = hInstance;
        ShowWindow(g_hMainWnd,SW_SHOW);
        UpdateWindow(g_hMainWnd);
     }
}


VOID WhileLoop(VOID)
{
    MSG msg;
    while(GetMessage(&msg,NULL,0,0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


VOID CreateMainControllers(HWND hMainWnd)
{
    g_hAddBt = CreateWindowW(L"button",L"ADD",WS_CHILD | WS_VISIBLE,16,16,64,32,hMainWnd,HMENU(ID_BT_ADD),g_inst,NULL);
    g_hRemoveBt = CreateWindowW(L"button",L"REMOVE",WS_CHILD | WS_VISIBLE,16,50,64,32,hMainWnd,HMENU(ID_BT),g_inst,NULL);
    g_hGenerateBt = CreateWindowW(L"button",L"GENERATE",WS_CHILD | WS_VISIBLE,56,164,128,32,hMainWnd,HMENU(ID_BT),g_inst,NULL);
    g_hListBox =    CreateWindowW(L"LISTBOX",L"...",WS_BORDER | WS_VISIBLE | WS_CHILD,96,16,120,132,hMainWnd,
                   HMENU(ID_MAIN_LISTBOX),g_inst,NULL);
}


VOID AddItemToListBox(HWND hwnd,int IDListBox,char* str,UINT index)
{
    int i = SendDlgItemMessage(g_hMainWnd,IDListBox,LB_ADDSTRING,index,(LPARAM)str);
}


char* PullTextFromTextField(HWND hwnd,UINT idControl)
{
      int len = GetWindowTextLength(GetDlgItem(hwnd,idControl));
       char *buff;
         buff = (char*)GlobalAlloc(GPTR,len+1);
         GetDlgItemText(hwnd,idControl,buff,len+1);
         return buff;
}

BOOL CALLBACK StuDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
         switch(Message)
              {
               case WM_INITDIALOG:
                  return TRUE;
               case WM_COMMAND:
                    switch(LOWORD(wParam))
                       {
                         case ID_BT_SAVE:
                             {
                                 char* name = PullTextFromTextField(hwnd,ID_EDIT_NAME);
                                 AddItemToListBox(g_hMainWnd,ID_MAIN_LISTBOX,name,0);
                                 EndDialog(hwnd,0);
                             }
                            break;
                         case IDOK:
                            EndDialog(hwnd,IDOK);
                         break;
                         case IDCANCEL:
                            EndDialog(hwnd,IDCANCEL);
                         break;
                         case ID_ADD_LESSON:
                             int ret = DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_TIME_DLG),hwnd,TimeDlgProc);
                         break;
                       }
               break;
               default:
               return FALSE;
              }
        return TRUE;
}

//TODO:convert two follow functions to one...
VOID InitDialogWithHours(HWND hDlg,int idCB)
{
    std::stringstream sstr;
    std::string tmp_string;
    char* minute;
    for(int i = 0;i<24;i++)
    {
        sstr << i;
        tmp_string = sstr.str();
        minute = (char*)tmp_string.c_str();
        SendDlgItemMessage(hDlg,idCB,CB_ADDSTRING,0,(LPARAM)minute);
        sstr.str("");
        sstr.clear();
    }
}

VOID InitDialogWithMinutes(HWND hDlg,int idCB)
{
    std::stringstream sstr;
    std::string tmp_string;
    char *minute;
    for(int i = 0;i<60;i++)
    {
        sstr << i;
        tmp_string = sstr.str();
        minute = (char*)tmp_string.c_str();
        SendDlgItemMessage(hDlg,idCB,CB_ADDSTRING,0,(LPARAM)minute);
        sstr.str("");
        sstr.clear();
    }
}

VOID InitDialogWithStrings(HWND hDlg)
{
    for(int i = 0;i<7;i++)
     {
       SendDlgItemMessage(hDlg,ID_CB_DAY,CB_ADDSTRING,0,(LPARAM)days[i]);
     }
}

UINT indexHourF,indexHourT,indexDay,indexMinF,indexMinT;

BOOL CALLBACK TimeDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
         switch(Message)
              {
               case WM_INITDIALOG:
                {
                   InitDialogWithStrings(hwnd);
                   InitDialogWithHours(hwnd,ID_CB_HOURF);
                   InitDialogWithHours(hwnd,ID_CB_HOURT);
                   InitDialogWithMinutes(hwnd,ID_CB_MINF);
                   InitDialogWithMinutes(hwnd,ID_CB_MINT);
                }
               break;
               case WM_COMMAND:
                   if (HIWORD(wParam) == CBN_SELCHANGE)
                   {
                     switch(LOWORD(wParam))
                     {
                     case ID_CB_DAY:
                       indexDay = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,
                        (WPARAM) 0, (LPARAM) 0);
                        printf("Day %d\n",indexDay);
                        break;
                     case ID_CB_HOURF:
                       indexHourF = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,
                        (WPARAM) 0, (LPARAM) 0);
                         printf("HourF %d\n",indexHourF);
                        break;
                     case ID_CB_HOURT:
                         indexHourT = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,
                         (WPARAM) 0, (LPARAM) 0);
                        printf("HourT %d\n",indexHourT);
                        break;
                     case ID_CB_MINF:
                         indexMinF = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,
                       (WPARAM) 0, (LPARAM) 0);
                        printf("MinF %d\n",indexMinF);
                        break;
                     case ID_CB_MINT:
                         indexMinT = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL,
                       (WPARAM) 0, (LPARAM) 0);
                        printf("MinT %d\n",indexMinT);
                        break;
                     }
                   }
                    switch(LOWORD(wParam))
                       {
                         case ID_BT_SAVE:
                             {
                               //  char* name = PullTextFromTextField(hwnd,ID_EDIT_NAME);
                               //  AddItemToListBox(g_hMainWnd,ID_MAIN_LISTBOX,name,0);
                                 EndDialog(hwnd,0);
                             }
                            break;
                         case IDOK:
                            EndDialog(hwnd,IDOK);
                         break;
                         case IDCANCEL:
                            EndDialog(hwnd,IDCANCEL);
                         break;
                       }
               break;
               default:
               return FALSE;
              }
        return TRUE;
}

 /* PAINTSTRUCT ps;
                 HDC hdc;
                 RECT rc;
                 hdc = BeginPaint(hwnd,&ps);
                 rc.left = 20;
                 rc.top = 20;
                 rc.right = 50;
                 rc.bottom = 50;
                 SetTextAlign(hdc,TA_CENTER);
                 SetTextColor(hdc,RGB(0,255,0));
                 FillRect(hdc,&rc,HBRUSH(CreateSolidBrush(RGB(200,0,0))));
                 if (Rectangle(hdc,100,100,200,200) == 0) MessageBox(hwnd,"fail ractengel","fail",MB_OK);
                 char* name = "hello";
                 TextOutA(hdc,250,30,name,5);
                 EndPaint(hwnd,&ps);

                 */
