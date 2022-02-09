//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -6;
int y = 6;

static int paddlesSides = 50;

int gameState = 0;

int pointsLeftPlayer = 0;
int pointsRightPlayer = 0;
int bounceCounter = 0;
bool fastBounce = false;

int resultBoxDim;

void speedUp(){
        if(abs(x) < 18){
                if(x>0) x++;
                else x--;
                if(y>0) y++;
                else y--;
        }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        ShowMessage("Witaj w grze ping pong!\n \nLewy gracz steruje wciskajac klawisze A oraz Z\nPrawy gracz steruje wciskajac strzalki do gory i w dol\n \nDla urozmaicenia zabawy:\nKiedy odbijesz pilke na srodku paletki, wowczas zmienisz jej kat odbicia i pilka przyspieszy.\nIm dlzej odbijasz, tym pilka szybciej przemieszcz sie.\nMozesz dowolnie zmieniac pole gry przed jej rozpoczeciem.\n\nMilej zabawy!\n\n");
        resultBoxDim = (newGameBtn->Top - pointPlayerLabel->Top) + newGameBtn->Height;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
      if(gameState == 0){
        Form1->BorderStyle = bsSizeable;
        LabelWelcome->Caption = "Zagrajmy w Ping Ponga!";
        LabelWelcome->Visible = true;
        newGameBtn->Visible = true;
        newGameBtn->Enabled = true;
        pointsLeftPlayer = 0;
        pointsRightPlayer = 0;
      } else if (gameState == 5) {
        Form1->BorderStyle = bsSizeable;
        LabelWelcome->Visible = true;
        pointsLeftPlayer = 0;
        pointsRightPlayer = 0;
      }
      bounceCounter = 0;
      fastBounce = false;

      //paddle at the same distance from sides
      paddleLeft->Left = paddlesSides;
      paddleRight->Left = BackGround->Width - paddleRight->Width - paddlesSides;
      //paddles at middle
      paddleLeft->Top = (BackGround->Height/2)-(paddleLeft->Height/2);
      paddleRight->Top = (BackGround->Height/2)-(paddleRight->Height/2);
      //ball at middle between paddles
      ball->Left = ((paddleRight->Left-paddleLeft->Left+paddleLeft->Width)/2)+paddleLeft->Left-(ball->Width/2);
      ball->Top = (BackGround->Height/2)-(ball->Height/2);
      //Label align to center
      LabelWelcome->Left = (BackGround->Width - LabelWelcome->Width) / 2;
      LabelWelcome->Top = 20;
      newGameBtn->Left = (BackGround->Width - newGameBtn->Width) / 2;
      nextRoundBtn->Left = (BackGround->Width - nextRoundBtn->Width) / 2;
      pointPlayerLabel->Left = (BackGround->Width - pointPlayerLabel->Width) / 2;
      resultLabel->Left = (BackGround->Width - resultLabel->Width) / 2;
      LabelHitQty->Left = (BackGround->Width - LabelHitQty->Width) / 2;

      pointPlayerLabel->Top = (BackGround->Height - resultBoxDim) / 2;
      resultLabel->Top = pointPlayerLabel->Top + 88;
      LabelHitQty->Top = pointPlayerLabel->Top + 136;
      nextRoundBtn->Top = pointPlayerLabel->Top + 176;
      newGameBtn->Top = pointPlayerLabel->Top + 232;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer_ballTimer(TObject *Sender)
{
        ball->Top  += y;
        ball->Left += x;
        //odbij od gornej sciany
        if((ball->Top - (abs(y)/2)) <= BackGround->Top) y = -y;
        //odbij od dolnej sciany
        if((ball->Top + ball->Height + (abs(y)/2)) >= BackGround->Height) y = -y;

        //left game over
        if(ball->Left <= paddleLeft->Left - (paddlesSides/2)){
                Timer_ball->Enabled = false;
                ball->Visible = false;
                pointsRightPlayer++;
                gameState = 3;
                pointPlayerLabel->Caption = "Punkt dla gracza prawego >";
                resultLabel->Caption = IntToStr(pointsLeftPlayer) + ":" + IntToStr(pointsRightPlayer);
                LabelHitQty->Caption =  "Ilosc odbic: " + IntToStr(bounceCounter);
                pointPlayerLabel->Visible = true;
                resultLabel->Visible = true;
                LabelHitQty->Visible = true;
                nextRoundBtn->Visible = true;
                nextRoundBtn->Enabled = true;
                newGameBtn->Visible = true;
                newGameBtn->Enabled = true;
                x = -6;
                y = 6;
        }

        //right game over
        if(ball->Left+ball->Width >= paddleRight->Left+paddleRight->Width + (paddlesSides/2)){
                Timer_ball->Enabled = false;
                ball->Visible = false;
                pointsLeftPlayer++;
                gameState = 3;
                pointPlayerLabel->Caption = "< Punkt dla gracza lewego";
                resultLabel->Caption = IntToStr(pointsLeftPlayer) + ":" + IntToStr(pointsRightPlayer);
                LabelHitQty->Caption =  "Ilosc odbic: " + IntToStr(bounceCounter);
                pointPlayerLabel->Visible = true;
                resultLabel->Visible = true;
                LabelHitQty->Visible = true;
                nextRoundBtn->Visible = true;
                nextRoundBtn->Enabled = true;
                newGameBtn->Visible = true;
                newGameBtn->Enabled = true;
                x = 6;
                y = 6;
        }

        //left paddle ball bounce fast
        if((ball->Top > (paddleLeft->Top+paddleLeft->Height/2-15)) && (ball->Top < (paddleLeft->Top+paddleLeft->Height/2+15)) &&
                ((ball->Left - (abs(y)/2)) <= (paddleLeft->Left+paddleLeft->Width))) {
                if(x<0) {
                        speedUp();
                        bounceCounter++;
                        if(!fastBounce){
                                x = -2*x;
                                //y = 2*y;
                        } else {
                                x = -x;
                        }
                        fastBounce = true;
                }
        }
        //left paddle ball bounce normal
        else if((ball->Top > (paddleLeft->Top-ball->Height/2)) && (ball->Top < (paddleLeft->Top+paddleLeft->Height-ball->Height/2)) &&
                ((ball->Left - (abs(y)/2)) <= (paddleLeft->Left+paddleLeft->Width))) {
                if(x<0) {
                        speedUp();
                        bounceCounter++;
                        if(!fastBounce) {
                                x = -x;
                        } else {
                                if(x%2) // speed may never increase (5*2=10 bounce-> (10+1)/2 = 5.5 = 5)
                                x = -((x+1)/2);
                                //y = y/2;
                                else
                                x = -(x/2);
                        }
                        fastBounce = false;
                }
        }

        //right paddle ball bounce fast
        if((ball->Top > (paddleRight->Top+paddleRight->Height/2-15)) && (ball->Top < (paddleRight->Top+paddleRight->Height/2+15)) &&
                ((ball->Left + ball->Width + (abs(y)/2)) >= (paddleRight->Left))) {
                if(x>0) {
                        speedUp();
                        bounceCounter++;
                        if(!fastBounce){
                                x = -2*x;
                                //y = 2*y;
                        } else {
                                x = -x;
                        }
                        fastBounce = true;
                }
        }
        //right paddle ball bounce normal
        else if((ball->Top > (paddleRight->Top-ball->Height/2)) && (ball->Top < (paddleRight->Top+paddleRight->Height-ball->Height/2)) &&
                ((ball->Left + ball->Width + (abs(y)/2)) >= (paddleRight->Left))) {
                if(x>0) {
                        speedUp();
                        if(!fastBounce) {
                                x = -x;
                        } else {
                                x = -(x/2);
                                //y = y/2;
                        }
                        fastBounce = false;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(gameState == 2) {
                if(Key == VK_UP) Timer_paddleRightUp->Enabled = true;
                if(Key == VK_DOWN) Timer_paddleRightDown->Enabled = true;
                if(Key == 'A' || Key == 'a') Timer_paddleLeftUp->Enabled = true;
                if(Key == 'Z' || Key == 'z') Timer_paddleLeftDown->Enabled = true;
        }
        if(Key == 'S' || Key == 's') {
                Timer_ball->Enabled = true;
                gameState = 2;
                LabelWelcome->Visible = false;
                Form1->BorderStyle = bsSingle;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_UP) Timer_paddleRightUp->Enabled = false;
        if(Key == VK_DOWN) Timer_paddleRightDown->Enabled = false;
        if(Key == 'A' || Key == 'a') Timer_paddleLeftUp->Enabled = false;
        if(Key == 'Z' || Key == 'z') Timer_paddleLeftDown->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_paddleRightUpTimer(TObject *Sender)
{
        if(paddleRight->Top > 0) paddleRight->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_paddleRightDownTimer(TObject *Sender)
{
        if(paddleRight->Top + paddleRight->Height < BackGround->Height) paddleRight->Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_paddleLeftUpTimer(TObject *Sender)
{
        if(paddleLeft->Top > 0) paddleLeft->Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer_paddleLeftDownTimer(TObject *Sender)
{
        if(paddleLeft->Top + paddleLeft->Height < BackGround->Height) paddleLeft->Top += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::newGameBtnClick(TObject *Sender)
{
        if(gameState==0){
                gameState = 1;
                LabelWelcome->Caption = "Wcisnij S, aby rozpoczac";
                newGameBtn->Visible = false;
                newGameBtn->Enabled = false;

                Form1->BorderStyle = bsSingle;



        } else if(gameState==3){
                if(Application->MessageBoxA("Czy napewno checsz zaczac od nowa?","Potwierdz",MB_YESNO | MB_ICONQUESTION) == IDYES){
                        gameState = 5;
                        pointPlayerLabel->Visible = false;
                        resultLabel->Visible = false;
                        LabelHitQty->Visible = false;
                        nextRoundBtn->Visible = false;
                        nextRoundBtn->Enabled = false;
                        newGameBtn->Visible = false;
                        newGameBtn->Enabled = false;
                        ball->Visible = true;
                        Form1->FormCreate(Owner);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::nextRoundBtnClick(TObject *Sender)
{
        if(gameState==3){
                Form1->FormCreate(Owner);
                gameState = 4;
                LabelWelcome->Caption = "Wcisnij S, aby rozpoczac";
                LabelWelcome->Visible = true;
                pointPlayerLabel->Visible = false;
                resultLabel->Visible = false;
                LabelHitQty->Visible = false;
                nextRoundBtn->Visible = false;
                nextRoundBtn->Enabled = false;
                newGameBtn->Visible = false;
                newGameBtn->Enabled = false;
                ball->Visible = true;
        }
}
//---------------------------------------------------------------------------

