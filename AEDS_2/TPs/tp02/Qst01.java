import java.util.Scanner;

class Qst01
{
	public void main(String[] args)
	{
		Data dataRegistro = new Data(10, 12, 2025);
		System.out.println("" + dataRegistro.get());
	}
/*
	class LeitorCsv
	{
					
	}

	class Veiculo()
	{

	}
*/


	class Data
	{
		private int dia;
		private int mes;
		private int ano;

		Data()
		{
			this(0, 0, 0);
		}
		Data(int dia, int mes, int ano)
		{
			this.dia = dia;
			this.mes = mes;
			this.ano = ano;
		}

		
		String format()
		{
			String formata = ("" + this.dia + "/" + this.mes + "/" + this.ano);
			return formata;
		}

		public String getter()

		{
			int dia = this.dia;
			int mes = this.mes;
			int ano = this.ano;
			return this.format;
		}

	}
}
