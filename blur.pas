unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, ExtDlgs, ExtCtrls, jpeg, StdCtrls, Math;

type

 TRGB=record  //masiva elements (piksela analogs), kas glaba info par RGB komponentem
  R,G,B: byte;  //RGB originalas vertibas
  newR, newG, newB: Byte; //RGB izmainitas vertibas
 end;

 TRGBTripleArray=array[Word]of TRGBTriple;  //Shis tips ir nepiecieshams Scanline procedurai un glaba attela pikselu rindu (TRGBTriple - tas ir RGB komponentes)
 pRGBTripleArray=^TRGBTripleArray;  //Shis ir pointeru masivs (glaba katra elementaa norades (adreses) uz TRGBTripleArray vertibam

  TForm1 = class(TForm)
    Image1: TImage;
    Button1: TButton;
    Button2: TButton;
    procedure ReadFromImage();
    procedure DrawFromArray(DrawMode: integer);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Filter(mode: Integer; koef: Integer);

  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  img:array of array of TRGB;   //tas ir attelu masivs, kura datus mes varam apstradat
  bmp: TBitmap; //tas ir globalais Bitmap attels, kas glaba informaciju par attelu

implementation

{$R *.dfm}

{ TForm1 }

procedure TForm1.FormCreate(Sender: TObject);
begin
  bmp:=TBitmap.Create;  //vispirms jaizveido bmp objektu
  bmp.LoadFromFile('test.bmp'); //tad jaielade failu bmp objektaa
  bmp.PixelFormat:=pf24bit; //uzstada attela pikselu formatu (no cik bitiem sastav krasu komponentes)
  Image1.Picture.Bitmap.Width:=bmp.Width; //Image1 laukam uz formas pieshkir bmp izmerus, lai pec tam korekti parzimet bmp uz Image1
  Image1.Picture.Bitmap.Height:=bmp.Height;
  Image1.Canvas.Draw(0,0,bmp);  //parzime bmp objektu uz Image1 lauka
  ReadFromImage();  //Shi procedura nolasa informaciju no bmp ieksha masivaa img
end;

procedure TForm1.ReadFromImage(); //Shi procedura nolasa informaciju no bmp ieksha masivaa img
var i,j:Integer;  //lai izskrietu cauri masivam/attelam
    row:pRGBTripleArray;  //rindas mainigais, kuru izmantos Scanline lai nolasit attela datus
begin
  SetLength(img, bmp.Width, bmp.Height);  //uzstada masiva img izmerus vienadus ar bmp objekta izmeriem

  for j:=0 to bmp.Height-1 do  //iziet cauri attelam pa vertikali (lai nolasit 1.,2.,3.,...n-to rindu)
   begin
     row:=bmp.ScanLine[j];  //nolasa rindu
     for i:=0 to bmp.Width-1 do //iziet cauri rindai pa horizontali (nolasa jau katra konkreta piksela komponenshu vertibas)
      begin
        img[i,j].R:=row[i].rgbtRed; //ieraksta masiva img sarkano komponeneti no pikselu rindas
        img[i,j].G:=row[i].rgbtGreen; //ieraksta masiva img zalo komponeneti no pikselu rindas
        img[i,j].B:=row[i].rgbtBlue; //ieraksta masiva img zilo komponeneti no pikselu rindas
      end;
   end;
end;

procedure TForm1.DrawFromArray(DrawMode: integer); //attelo masiva datus lietotajam
var i,j:Integer; //lai izskrietu cauri masivam/attelam
    row:pRGBTripleArray; //rindas mainigais, kuru izmantos Scanline lai nolasit attela datus
begin
  for j:=0 to bmp.Height-1 do //iziet cauri attelam pa vertikali (lai nolasit 1.,2.,3.,...n-to rindu)
    begin
     row:=bmp.ScanLine[j];  //nolasa rindu
     for i:=0 to bmp.Width-1 do //iziet cauri rindai pa horizontali (nolasa jau katra konkreta piksela komponenshu vertibas)
      case DrawMode of //atteloshanas rezhims (originalais attels, vai modificets attels)
      0: begin  //originals
          row[i].rgbtRed:=img[i,j].R; //ieraksta bmp objektaa originalo sarkano komponenti no masiva img
          row[i].rgbtGreen:=img[i,j].G; //ieraksta bmp objektaa originalo  zalo komponenti no masiva img
          row[i].rgbtBlue:=img[i,j].B; //ieraksta bmp objektaa originalo zilo komponenti no masiva img
         end;
      1: begin  //modificets
          row[i].rgbtRed:=img[i,j].newR; //ieraksta bmp objektaa modificeto sarkano komponenti no masiva img
          row[i].rgbtGreen:=img[i,j].newG;  //ieraksta bmp objektaa modificeto  zalo komponenti no masiva img
          row[i].rgbtBlue:=img[i,j].newB;  //ieraksta bmp objektaa modificeto zilo komponenti no masiva img
         end;
      end;
    end;
  Image1.Canvas.Draw(0,0,bmp);  //parzime bmp objektu Image1 laukaa
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  DrawFromArray(0);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Filter(0,9);
  DrawFromArray(1);
end;

procedure TForm1.Filter(mode: Integer; koef: Integer);
const
  F0: Array [-1..1,-1..1] of Integer =
    (
      (8,1,1),
      (1,1,1),
      (1,1,1)
    );
var i, j, fi, fj, r, g, b: Integer;
begin

  for i:= 1 to High(img)-1 do
    for j:= 1 to High(img[0])-1 do begin
      r:= 0;
      g:= 0;
      b:= 0;
      for fi:= -1 to 1 do
        for fj:= -1 to 1 do begin
          r:= r + img[i+fi, j+fj].R * F0[fi,fj];
          g:= r + img[i+fi, j+fj].G * F0[fi,fj];
          b:= r + img[i+fi, j+fj].B * F0[fi,fj];
        end;
      img[i,j].newR:= Max(Min(r div koef, 255), 0);
      img[i,j].newG:= Max(Min(g div koef, 255), 0);
      img[i,j].newB:= Max(Min(b div koef, 255), 0);
    end;

end;

end.
