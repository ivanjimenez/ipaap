#define M(a,i,j,lda) (a)[(i)+(j)*lda]

void print_error(char *rutina, char *texto_err);
double *dvector(int nh);
int *ivector(int nh);
double *dmatrix(int nfh, int nch);
int *imatrix(int nfh, int nch);
