import java.util.Scanner;

class Qst3
{
    static boolean isVogal(char c)
    {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return true;
        return false;
    }

    static boolean isLetra(char c)
    {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return true;
        return false;
    }

    static boolean soVogais(String s)
    {
        for (int i = 0; i < s.length(); i++)
        {
        	if (isVogal(s.charAt(i)) == false)
                return false;
        } 
        return true;
    }

    static boolean soConsoantes(String s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (isLetra(s.charAt(i)) == false || isVogal(s.charAt(i)) == true) return false;
        }
        return true;
    }

    static boolean isInteiro(String s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            char c = s.charAt(i);
            if (i == 0 && (c == '-' || c == '+'))continue;
            if (c < '0' || c > '9') return false;
        }
        return true;
    }

    static boolean isReal(String s)
    {
        int pontos = 0;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s.charAt(i);
            if (i == 0 && (c == '-' || c == '+')) continue;
            if (c == '.' || c == ',') pontos++;
            else if (c < '0' || c > '9') return false;
        }
        if (pontos > 1) return false;
        return true;
    }

    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        boolean flag = true;
        while (flag && scan.hasNextLine())
        {
            String linha = scan.nextLine().replace("\r", "");
            if (linha.equals("FIM") || linha.equals("fim")) flag = false;
            else
            {
                if (soVogais(linha)) System.out.print("SIM ");
                else System.out.print("NAO ");
                    
                if (soConsoantes(linha)) System.out.print("SIM ");
                else System.out.print("NAO ");
                    
                if (isInteiro(linha)) System.out.print("SIM ");
                else System.out.print("NAO ");

                if (isReal(linha)) System.out.println("SIM");
                else System.out.println("NAO");
            }
        }
        scan.close();
    }
}
