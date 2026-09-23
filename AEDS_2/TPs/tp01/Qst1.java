import java.util.Scanner;

public class Qst1
{
	public static String cifra(String frase)
	{
		String resultado = "";
		for(int i = 0; i < frase.length(); i++)
		{
			char letra = frase.charAt(i);
			resultado += (char) (letra + 3);
		}
		return resultado;
	}


	public static void main(String[] args)
	{
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
				String codigo = cifra(linha);
				System.out.println(codigo);
			}
		}
		scan.close();
	}
}
