#ifndef __PRINTTEST__H_
#define __PRINTTEST__H_

// #define T_USB 1	
// #define MODEL "MP-4200"
// #define CONEX "USB"
// #define PARAM 0
#define T_RS232 2
#define MODEL "MP-4200"
#define COM_PORT "/dev/ttyACM0"
#define BAUD_R 57600
//#define BAUD_R 115200
#define OPEN 0

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

int 	AbreConexaoImpressora (int tipo, const char *modelo, const char *conexao, int parametro);

int 	FechaConexaoImpressora ();

int 	EspacamentoEntreLinhas (int tamanho);

int 	ImpressaoTexto (const char *dados, int posicao, int stilo, int tamanho);

int 	Corte (int avanco);

int 	CorteTotal (int avanco);

int 	ImpressaoQRCode (const char *dados, int tamanho, int nivelCorrecao);
 
int 	ImpressaoPDF417 (int numCols, int numRows, int width, int height, int errCorLvl, int options, const char *dados);
 
int 	ImpressaoCodigoBarras (int tipo, const char *dados, int altura, int largura, int HRI);
 
int 	AvancaPapel (int linhas);
 
int 	StatusImpressora (int param);
 
int 	AbreGavetaElgin ();
 
int 	AbreGaveta (int pino, int ti, int tf);
 
int 	InicializaImpressora ();
 
int 	DefinePosicao (int posicao);
 
int 	SinalSonoro (int qtd, int tempoInicio, int tempoFim);
 
int 	DirectIO (unsigned char *writeData, unsigned int writeNum, unsigned char *readData, unsigned int *readNum);
 
int 	ImprimeImagemMemoria (const char *key, int scala);
 
int 	ImprimeXMLSAT (const char *dados, int param);
int 	ImprimeXMLCancelamentoSAT (const char *dados, const char *assQRCode, int param);
 
int 	ImprimeXMLNFCe (const char *dados, int indexcsc, const char *csc, int param);
 
int 	ImprimeXMLCancelamentoNFCe (const char *dados, int param);
int 	ModoPagina ();
 
int 	DirecaoImpressao (int direcao);
 
int 	DefineAreaImpressao (int oHorizontal, int oVertical, int dHorizontal, int dVertical);
int 	PosicaoImpressaoHorizontal (int nLnH);
int 	PosicaoImpressaoVertical (int nLnH);
int 	ImprimeModoPagina ();
int 	LimpaBufferModoPagina ();
int 	ImprimeMPeRetornaPadrao ();
int 	ModoPadrao ();
char * 	GetVersaoDLL ();
int 	ImprimeCupomTEF (const char *dados);
int 	ImprimeImagem (const char *path);


#ifdef __cplusplus
}
#endif




#endif //__PRINTTEST__H_
