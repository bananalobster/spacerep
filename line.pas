unit UnitMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Image1: TImage;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var x0, y0, x1, y1, x, y, dx, dy, ix, iy, i, p: Integer;
begin

  x0 := StrToInt(Edit1.Text);
  y0 := StrToInt(Edit2.Text);
  x1 := StrToInt(Edit3.Text);
  y1 := StrToInt(Edit4.Text);
  x := 0;
  y := 0;
  dx := abs(x1-x0);
  dy := abs(y1-y0);

  if (x1>x0) then
    ix := 1
  else
    ix := -1;
  if (y1>y0) then
    iy := 1
  else
    iy := -1;

  if (dx>dy) then begin
    p := 2*dy - dx;
    for i:= 0 to dx do begin
      if (p>0) then begin
        x:= x + ix;
        y:= y + iy;
        p:= p + 2*dy - 2*dx;
      end
      else begin
        x:= x + ix;
        p:= p + 2*dy;
      end;
      Image1.Canvas.Pixels[x0+x,y0+y] := clBlack;
    end;
  end
  else begin
    p := 2*dx - dy;
    for i:= 0 to dy do begin
      if (p>0) then begin
        x:= x + ix;
        y:= y + iy;
        p:= p + 2*dx - 2*dy;
      end
      else begin
        y:= y + iy;
        p:= p + 2*dx;
      end;
      Image1.Canvas.Pixels[x0+x,y0+y] := clBlack;
    end;
  end;

end;

end.
