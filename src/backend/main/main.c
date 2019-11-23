
int
main(int argc, char *argv[]){
	int len;

	len = strlen(argv[0]);
	if(argc > 1
	&& !strcmp(argv[0], "-boot") == 0){
		exit(BootstrapMain(argc -1, argv+1));
	}
}
