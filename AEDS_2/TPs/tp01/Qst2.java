import java.util.Scanner;
import java.util.Random;

public class Qst2
{
	public static Random gerador = new Random();

	public static String altera(String frase)
	{
		char letra1 = (char) ('a' + (Math.abs(gerador.nextInt())%26));
		char letra2 = (char) ('a' + (Math.abs(gerador.nextInt())%26));
		String resultado = "";
		for(int i = 0; i < frase.length(); i++)
		{
			char atual = frase.charAt(i);
			if(atual == letra1)
			{
				resultado += letra2;
			}
			else
			{
				resultado += atual;
			}
		}
		return resultado;
	}

	public static void main(String[] args)
	{
		gerador.setSeed(4);
		Scanner scan = new Scanner(System.in);
		boolean flag = true;
		while(flag && scan.hasNextLine())
		{
			String linha = scan.nextLine();
			if(linha.equals("FIM") || linha.equals("fim"))
			{
				flag = false;
			}
			else
			{
				String codigo = altera(linha);
				System.out.println(codigo);
			}
		}
		scan.close();
	}
}
