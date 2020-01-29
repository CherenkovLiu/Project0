package Project0.Semantic;

import java.util.LinkedList;

import Project0.Extend.*;

public class Lexer {
    // diagnostic information
    private LinkedList<String> _diagnostic = new LinkedList<String>();

    public LinkedList<String> Diagnostic() {
        return this._diagnostic;
    }

    private char[] sourceCode;
    private int index;
    private int lineNumber;

    public Lexer(String sourceCode) {
        this.sourceCode = (sourceCode + "\0").toCharArray();
        this.index = 0;
        this.lineNumber = 1;
    }

    private char Peek() {
        return sourceCode[index + 1 >= sourceCode.length ? sourceCode.length - 1 : index + 1];
    }

    private char Pop() {
        return sourceCode[index++];
    }

    private char Current() {
        return sourceCode[index];
    }

    private Token readNumber() {
        boolean isNumber = false;
        String number = String.valueOf(Pop());
        while (true) {
            char current = Current();
            if (Character.isDigit(current)) {
                number += current;
                if (Pop() == '\0')
                    break;
            } else if (current == '.' && Character.isDigit(Peek()) && !isNumber) {
                isNumber = true;
                number += current;
                Pop();
            } else
                break;
        }
        return new Token(isNumber ? TokenType.NUMBER : TokenType.INTEGER, number);
    }

    private Token readLiteral() throws Exception {
        String literal = String.valueOf(Pop());
        while (true) {
            char current = Current();
            if (Character.isLetterOrDigit(current) || current == '_') {
                literal += current;
                if (Pop() == '\0')
                    break;
            } else
                break;
        }
        return new Token(EString.isKeyword(literal) ? EString.getKeywordTokenType(literal) : TokenType.IDENTIFIER,
                literal);
    }

    private Token readSymbol() throws Exception {
        String symbol = String.valueOf(Pop());
        while (true) {
            char current = Current();
            if (current == '+' || current == '-' || current == '&' || current == '|' || current == '=') {
                Pop();
                symbol += current;
            } else
                break;
        }
        return new Token(EString.getSymbol(symbol), symbol);
    }

    private Token readString() throws Exception {
        String str = "";
        Pop();
        while (true) {
            var current = Current();
            if (current == '"') {
                Pop();
                break;
            } else if (current == '\0')
                throw new Exception(String.format("Expected a EOF in string in line %d", lineNumber));
            else
                str += Pop();
        }
        return new Token(TokenType.STRING, str);
    }

    private void skipBlank() {
        while (true) {
            char current = Current();
            if (current == ' ' || current == '\n' || current == '\r' || current == '\t' || current == '\f') {
                if (current == '\n')
                    lineNumber++;
                Pop();
            } else
                break;
        }
    }

    public Token nextToken() throws Exception {
        skipBlank();
        char current = Current();
        if (Character.isDigit(current))
            return readNumber();
        else if (Character.isLetter(current))
            return readLiteral();
        else if (current == '(' || current == ')' || current == '[' || current == ']' || current == '{'
                || current == '}' || current == ':' || current == ',' || current == ';' || current == '.') {
            Pop();
            return new Token(EString.getSeperator(String.valueOf(current)), String.valueOf(current));
        } else if (current == '+' || current == '-' || current == '*' || current == '/' || current == '&'
                || current == '|' || current == '^' || current == '~' || current == '!' || current == '='
                || current == '>' || current == '<') {
            try {
                return readSymbol();
            } catch (Exception err) {
                _diagnostic.add(err.getMessage() + String.format(" [line %d]", lineNumber));
                return new Token(TokenType.BAD_TOKEN, null);
            }
        } else if (current == '"') {
            try {
                return readString();
            } catch (Exception err) {
                _diagnostic.add(err.getMessage() + String.format(" [line %d]", lineNumber));
                return new Token(TokenType.BAD_TOKEN, null);
            }
        } else if (current == '\0')
            return new Token(TokenType.EOF, "\0");
        else {
            index++;
            _diagnostic.add(String.format("Error : Unexpected symbol '%c' [line %d]", current, lineNumber));
            return new Token(TokenType.BAD_TOKEN, null);
        }
    }

    public Token[] tokenize() throws Exception {
        LinkedList<Token> tokenList = new LinkedList<Token>();
        while (true) {
            var tmp = nextToken();
            tokenList.add(tmp);
            if (tmp.type == TokenType.EOF)
                break;
        }
        return tokenList.toArray(new Token[tokenList.size()]);
    }

    public String toJson() throws Exception {
        var fakeList = new LinkedList<String>();
        var tokenized = tokenize();
        for (var token : tokenized)
            fakeList.add((new FakeToken(token.type, token.value)).toJson());
        return "[" + String.join(",", fakeList.toArray(new String[fakeList.size()])) + "]";
    }

    private class FakeToken {
        public String type;
        public String value;

        public FakeToken(TokenType type, String value) {
            this.type = type.toString();
            this.value = value;
        }

        public String toJson() {
            return String.format("{\"type\":\"%s\",\"value\":\"%s\"}", type, value);
        }
    }
}