Token* nextToken() {
    Token* token = nullptr;
    char c = nextChar();
    
    while (1) {
        switch (state) {
            case 0: {
                // Estado inicial del autómata. Aquí se decide qué tipo de token reconocer.
                
                if (c == ' ' || c == '\t') {
                    // Si el carácter es un espacio en blanco o una tabulación, avanzamos al siguiente carácter.
                    c = nextChar();
                } else if (isalpha(c)) {
                    // Si el carácter es una letra, pasamos al estado 1 para reconocer palabras reservadas y IDs.
                    state = 1;
                } else if (isdigit(c)) {
                    // Si el carácter es un dígito, pasamos al estado 2 para reconocer números.
                    state = 2;
                } else if (c == ':') {
                    // Si el carácter es ':', cambiamos al estado 3 para reconocer etiquetas.
                    state = 3;
                } else if (c == '\n') {
                    // Si el carácter es un salto de línea, pasamos al estado 4 para reconocer fin de línea.
                    state = 4;
                } else if (c == '\0') {
                    // Si el carácter es el final del archivo, pasamos al estado 5 para reconocer fin de archivo.
                    state = 5;
                } else {
                    // Si el carácter no coincide con ninguno de los casos anteriores, es un error.
                    token = new Token(ERR, std::string(1, c)); // Crear un token de error.
                    state = 0; // Regresamos al estado inicial para reconocer el próximo token.
                }
                break;
            }
            case 1: {
                // Estado para reconocer palabras reservadas y IDs.
                startLexeme();

                while (isalnum(c) || c == '_') {
                    // Mientras el carácter actual sea alfanumérico o un '_', avanzamos en el lexema.
                    c = nextChar();
                }

                rollBack(); // Retrocedemos para no incluir el último carácter no alfanumérico.
                std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                
                Token* keywordToken = isKW(lexeme); // Verificamos si el lexema es una palabra reservada o un ID.
                if (keywordToken) {
                    // Si es una palabra reservada, usamos el token de palabra reservada.
                    token = keywordToken;
                } else {
                    // Si no es una palabra reservada, asumimos que es un ID.
                    token = new Token(ID, lexeme);
                }

                state = 0; // Regresamos al estado inicial para reconocer el próximo token.
                break;
            }
            case 2: {
                // Estado para reconocer números.
                startLexeme();

                while (isdigit(c)) {
                    // Mientras el carácter actual sea un dígito, avanzamos en el lexema.
                    c = nextChar();
                }

                rollBack(); // Retrocedemos para no incluir el último carácter no numérico.
                std::string lexeme = getLexema(); // Obtenemos el lexema acumulado.
                token = new Token(NUM, lexeme); // Creamos un token de tipo NUM con el lexema.

                state = 0; // Regresamos al estado inicial.
                break;
            }
            case 3: {
                // Estado para reconocer etiquetas.
                startLexeme();

                while (isalnum(c) || c == '_') {
                    // Mientras el carácter actual sea alfanumérico o un '_', avanzamos en el lexema.
                    c = nextChar();
                }

                if (c == ':') {
                    // Si el próximo carácter es ':', hemos reconocido una etiqueta.
                    std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                    token = new Token(LABEL, lexeme); // Creamos un token de tipo LABEL con el lexema.
                    state = 0; // Regresamos al estado inicial.
                } else {
                    // Si el próximo carácter no es ':', es un error.
                    token = new Token(ERR, getLexema());
                    state = 0; // Regresamos al estado inicial.
                }

                break;
            }
            case 4: {
                // Estado para reconocer fin de línea.
                token = new Token(EOL, "\n"); // Creamos un token de tipo EOL.
                state = 0; // Regresamos al estado inicial.
                break;
            }
            case 5: {
                // Estado para reconocer fin de archivo.
                token = new Token(END); // Creamos un token de tipo END.
                return token; // Salimos del bucle ya que no hay más tokens.
            }
        }
    }
}
