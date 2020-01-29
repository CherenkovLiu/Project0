package Project0.Extend;

import java.util.HashSet;
import Project0.Semantic.*;

public class EString {
    public static HashSet<String> keywordSet = new HashSet<String>() {
        private static final long serialVersionUID = -4389572816283513483L;
        {
            add("if");
            add("else");
            add("while");
            add("true");
            add("false");
            add("this");
            add("def");
            add("return");
            add("switch");
            add("case");
            add("do");
            add("class");
            add("public");
            add("private");
            add("object");
            add("int");
            add("long");
            add("short");
            add("double");
            add("string");
            add("char");
            add("void");
        }
    };

    public static Boolean isKeyword(String identifier) {
        return keywordSet.contains(identifier);
    }

    public static TokenType getKeywordTokenType(String keyword) throws Exception {
        if (EString.isKeyword(keyword)) {
            switch (keyword) {
            case "int":
            case "double":
            case "long":
            case "bool":
            case "string":
            case "char":
            case "void":
                return TokenType.BUILDIN_TYPE;
            case "if":
                return TokenType.KW_IF;
            case "else":
                return TokenType.KW_ELSE;
            case "while":
                return TokenType.KW_WHILE;
            case "true":
                return TokenType.KW_TRUE;
            case "false":
                return TokenType.KW_FALSE;
            case "this":
                return TokenType.KW_THIS;
            case "def":
                return TokenType.KW_DEFINE;
            case "return":
                return TokenType.KW_RETURN;
            case "switch":
                return TokenType.KW_SWITCH;
            case "case":
                return TokenType.KW_CASE;
            case "do":
                return TokenType.KW_DO;
            case "class":
                return TokenType.KW_CLASS;
            case "public":
                return TokenType.KW_PUBLIC;
            case "private":
                return TokenType.KW_PRIVATE;
            case "object":
                return TokenType.KW_WHILE;
            default:
                throw new Exception(String.format("Error : Undefined keyword %s", keyword));
            }
        } else
            throw new Exception(String.format("Error : '%s' is not a keyword", keyword));
    }

    public static TokenType getSeperator(String sep) throws Exception {
        switch (sep) {
        case "(":
            return TokenType.OPEN_PAREN;
        case ")":
            return TokenType.CLOSE_PAREN;
        case "[":
            return TokenType.OPEN_SQU;
        case "]":
            return TokenType.CLOSE_SQU;
        case "{":
            return TokenType.OPEN_BRAC;
        case "}":
            return TokenType.CLOSE_BRAC;
        case ":":
            return TokenType.COLON;
        case ",":
            return TokenType.COMMA;
        case ";":
            return TokenType.SEMICOLON;
        case ".":
            return TokenType.DOT;
        default:
            throw new Exception(String.format("Error : Undefined seperator '%s'", sep));
        }
    }

    public static TokenType getSymbol(String sym) throws Exception {
        switch (sym) {
        case "+":
            return TokenType.OP_PLUS;
        case "-":
            return TokenType.OP_MINUS;
        case "*":
            return TokenType.OP_TIMES;
        case "/":
            return TokenType.OP_DIVISION;
        case "&":
            return TokenType.OP_AND;
        case "|":
            return TokenType.OP_OR;
        case "^":
            return TokenType.OP_NOR;
        case "~":
            return TokenType.OP_NOT;
        case "!":
            return TokenType.OP_LNOT;
        case ">":
            return TokenType.OP_GREATER;
        case "<":
            return TokenType.OP_LESSER;
        case "&&":
            return TokenType.OP_LAND;
        case "||":
            return TokenType.OP_LOR;
        case ">=":
            return TokenType.OP_GREATER_EQUAL;
        case "<=":
            return TokenType.OP_LESSER_EQUAL;
        case "==":
            return TokenType.OP_EQUAL;
        case "=":
            return TokenType.OP_ASSIGN;
        case "++":
            return TokenType.OP_INCREASE;
        case "--":
            return TokenType.OP_DECREASE;
        default:
            throw new Exception(String.format("Error : '%s' is an illegal symbol", sym));
        }
    }
}