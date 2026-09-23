import java.util.Scanner;

class Qst11
{
    static String inverte_rec(String s, int i)
    {
        if(i == s.length()) return "";
        return inverte_rec(s, i + 1) + s.charAt(i);
    }

    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        boolean flag = true;
        while(flag && scan.hasNextLine())
        {
            String linha = scan.nextLine().replace("\r", "");
            if(linha.equals("FIM") || linha.equals("fim")) flag = false;
            else System.out.println(inverte_rec(linha, 0));
        }
        scan.close();
    }
}
