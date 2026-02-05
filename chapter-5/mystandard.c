char *getline(char arr[], size_t maxsize) {

	for (int c, *p=arr; (c=getchar()) != '\n'; ++p) {
		if (c == EOF) 
			break;
		*p = c;
		if (p-arr < maxsize-1) {
			*(++p) = '\0';
			return arr;
		}
	}

	*p = '\0';
	return arr;
}

	

