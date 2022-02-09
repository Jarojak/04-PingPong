//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *BackGround;
        TTimer *Timer_ball;
        TImage *ball;
        TImage *paddleLeft;
        TImage *paddleRight;
        TTimer *Timer_paddleLeftUp;
        TTimer *Timer_paddleLeftDown;
        TTimer *Timer_paddleRightUp;
        TTimer *Timer_paddleRightDown;
        TButton *newGameBtn;
        TButton *nextRoundBtn;
        TLabel *LabelHitQty;
        TLabel *pointPlayerLabel;
        TLabel *resultLabel;
        TLabel *LabelWelcome;
        void __fastcall Timer_ballTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Timer_paddleRightUpTimer(TObject *Sender);
        void __fastcall Timer_paddleRightDownTimer(TObject *Sender);
        void __fastcall Timer_paddleLeftUpTimer(TObject *Sender);
        void __fastcall Timer_paddleLeftDownTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall newGameBtnClick(TObject *Sender);
        void __fastcall nextRoundBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
