import java.util.Scanner;

class Qst8
{
    static boolean valida_senha(String senha)
    {
        if(senha.length() < 8) return false;
        boolean tem_mai = false;
        boolean tem_min = false;
        boolean tem_num = false;
        boolean tem_esp = false;
        for(int i = 0; i < senha.length(); i++)
            if(senha.charAt(i) >= 'A' && senha.charAt(i) <= 'Z') tem_mai = true;
            else if(senha.charAt(i) >= 'a' && senha.charAt(i) <= 'z') tem_min = true;
            else if(senha.charAt(i) >= '0' && senha.charAt(i) <= '9') tem_num = true;
            else tem_esp = true;
        return tem_mai && tem_min && tem_num && tem_esp;
    }

    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
        boolean flag = true;
        while(flag && scan.hasNextLine())
        {
            String linha = scan.nextLine().replace("\r", "");
            if(linha.equals("FIM") || linha.equals("fim")) flag = false;
            else if(valida_senha(linha)) System.out.println("SIM");
            else System.out.println("NAO");
        }
        scan.close();
    }
}
