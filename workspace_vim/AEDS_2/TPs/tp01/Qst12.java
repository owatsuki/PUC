import java.util.Scanner;

class Qst12
{
    static int soma_rec(String s, int i)
    {
        if(i == s.length()) return 0;
        return (s.charAt(i) - '0') + soma_rec(s, i + 1);
    }

    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        boolean flag = true;
        while(flag && scan.hasNextLine())
        {
            String linha = scan.nextLine().replace("\r", "");
            if(linha.equals("FIM") || linha.equals("fim")) flag = false;
            else System.out.println(soma_rec(linha, 0));
        }
        scan.close();
    }
}
