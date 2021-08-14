#define     NAME    "Section1.2 window base"  //�^�C�g���o�[�ɕ\������e�L�X�g
#include    <windows.h>

//�v���g�^�C�v�錾
LRESULT  CALLBACK   WndProc(HWND, UINT, WPARAM, LPARAM);
int      WINAPI     WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

//Windws �C�x���g�p�֐�
LRESULT  CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    
    //�n���ꂽ message ����A�C�x���g�̎�ނ���͂���
    switch(msg){
    //----�I������----
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    //----�f�t�H���g�̏���----
    default :
        return DefWindowProc(hWnd,msg,wParam,lParam);
    }
    
    return 0L;
}

//Windows Main �֐�
int  WINAPI  WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow ){
    HWND        hWnd;
    MSG         msg;
    
    // Set up and register window class
    WNDCLASS wc = { CS_CLASSDC,
                    WndProc,                                //�C�x���gcallback�֐�
                    0,
                    0,
                    hInstance,
                    NULL,                                   //�A�C�R��
                    LoadCursor( NULL, IDC_ARROW ),          //�}�E�X�J�[�\��
                    (HBRUSH) GetStockObject( WHITE_BRUSH ), //�w�i�F
                    NULL,                                   //���j���[
                    NAME };                                 //�N���X��
    if( RegisterClass( &wc ) == 0 ) return FALSE;
    
    //�E�C���h�E����
    hWnd = CreateWindow( NAME,                  //�^�C�g���o�[�e�L�X�g
                         NAME,                  //�N���X��
                         WS_OVERLAPPEDWINDOW,   //�E�C���h�E�X�^�C��
                         CW_USEDEFAULT,         //�E�C���h�E����x���W
                         CW_USEDEFAULT,         //�E�C���h�E����y���W
                         CW_USEDEFAULT,         //�E�C���h�E��
                         CW_USEDEFAULT,         //�E�C���h�E����
                         NULL,                  //�e�E�C���h�E�̃n���h��
                         NULL,
                         hInstance,
                         NULL );
    if( !hWnd ) return FALSE;
    
    ShowWindow( hWnd, nCmdShow );     //Window ��\��
    UpdateWindow( hWnd );             //�\����������
    SetFocus( hWnd );                 //�t�H�[�J�X��ݒ�
    
    while( GetMessage( &msg, NULL, 0, 0 ) ){
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    return msg.wParam;
}
