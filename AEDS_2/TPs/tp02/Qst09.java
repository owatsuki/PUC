import java.io.File;
import java.util.Scanner;

public class Qst09
{
    public static void main(String[] args)
    {
        Veiculo[] todos = LeitorCsv.ler("/tmp/veiculos.csv");
        if (todos == null || todos.length == 0)
        {
            return;
        }

        Lista lista = new Lista(1000);

        Scanner sc = new Scanner(System.in);
        while (sc.hasNextInt())
        {
            int id = sc.nextInt();
            if (id == -1) break;
            for (int i = 0; i < todos.length; i++)
            {
                if (todos[i] != null && todos[i].getId() == id)
                {
                    lista.inserirFim(todos[i]);
                    break;
                }
            }
        }

        int n = sc.nextInt();
        sc.nextLine();

        for (int k = 0; k < n; k++)
        {
            String linha = sc.nextLine();
            String[] p = linha.split(" ");
            String cmd = p[0];

            if (cmd.equals("II"))
            {
                int id = Integer.parseInt(p[1]);
                Veiculo v = buscar(todos, id);
                if (v != null) lista.inserirInicio(v);
            }
            else if (cmd.equals("IF"))
            {
                int id = Integer.parseInt(p[1]);
                Veiculo v = buscar(todos, id);
                if (v != null) lista.inserirFim(v);
            }
            else if (cmd.equals("I*"))
            {
                int pos = Integer.parseInt(p[1]);
                int id = Integer.parseInt(p[2]);
                Veiculo v = buscar(todos, id);
                if (v != null) lista.inserir(v, pos);
            }
            else if (cmd.equals("RI"))
            {
                Veiculo v = lista.removerInicio();
                if (v != null)
                {
                    System.out.println("(R)" + v.getMarca() + " " + v.getModelo());
                }
            }
            else if (cmd.equals("RF"))
            {
                Veiculo v = lista.removerFim();
                if (v != null)
                {
                    System.out.println("(R)" + v.getMarca() + " " + v.getModelo());
                }
            }
            else if (cmd.equals("R*"))
            {
                int pos = Integer.parseInt(p[1]);
                Veiculo v = lista.remover(pos);
                if (v != null)
                {
                    System.out.println("(R)" + v.getMarca() + " " + v.getModelo());
                }
            }
        }

        lista.mostrar();
        sc.close();
    }

    public static Veiculo buscar(Veiculo[] vet, int id)
    {
        for (int i = 0; i < vet.length; i++)
        {
            if (vet[i] != null && vet[i].getId() == id)
            {
                return vet[i];
            }
        }
        return null;
    }
}

class Lista
{
    private Veiculo[] array;
    private int n;

    Lista(int tamanho)
    {
        array = new Veiculo[tamanho];
        n = 0;
    }

    public void inserirInicio(Veiculo v)
    {
        for (int i = n; i > 0; i--)
        {
            array[i] = array[i - 1];
        }
        array[0] = v;
        n++;
    }

    public void inserir(Veiculo v, int pos)
    {
        for (int i = n; i > pos; i--)
        {
            array[i] = array[i - 1];
        }
        array[pos] = v;
        n++;
    }

    public void inserirFim(Veiculo v)
    {
        array[n] = v;
        n++;
    }

    public Veiculo removerInicio()
    {
        if (n == 0) return null;
        Veiculo resp = array[0];
        for (int i = 0; i < n - 1; i++)
        {
            array[i] = array[i + 1];
        }
        n--;
        return resp;
    }

    public Veiculo remover(int pos)
    {
        if (n == 0) return null;
        Veiculo resp = array[pos];
        for (int i = pos; i < n - 1; i++)
        {
            array[i] = array[i + 1];
        }
        n--;
        return resp;
    }

    public Veiculo removerFim()
    {
        if (n == 0) return null;
        n--;
        return array[n];
    }

    public void mostrar()
    {
        for (int i = 0; i < n; i++)
        {
            System.out.println(array[i].format());
        }
    }
}

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

    public int getDia() { return this.dia; }
    public int getMes() { return this.mes; }
    public int getAno() { return this.ano; }

    public static Data parseData(String s)
    {
        String[] partes = s.split("-");
        int ano = Integer.parseInt(partes[0]);
        int mes = Integer.parseInt(partes[1]);
        int dia = Integer.parseInt(partes[2]);
        return new Data(dia, mes, ano);
    }

    public String format()
    {
        return String.format("%02d/%02d/%04d", this.dia, this.mes, this.ano);
    }
}

class Veiculo
{
    private int id;
    private String marca;
    private String modelo;
    private int ano;
    private String categoria;
    private String[] combustivel;
    private int cilindros;
    private double cilindrada;
    private String transmissao;
    private String tracao;
    private double consumoCidade;
    private double consumoEstrada;
    private double co2;
    private boolean turbo;
    private Data dataRegistro;

    Veiculo()
    {
        this(0, "", "", 0, "", new String[0], 0, 0.0, "", "", 0.0, 0.0, 0.0, false, new Data());
    }

    Veiculo(int id, String marca, String modelo, int ano, String categoria, String[] combustivel, int cilindros, double cilindrada, String transmissao, String tracao, double consumoCidade, double consumoEstrada, double co2, boolean turbo, Data dataRegistro)
    {
        this.id = id;
        this.marca = marca;
        this.modelo = modelo;
        this.ano = ano;
        this.categoria = categoria;
        this.combustivel = combustivel;
        this.cilindros = cilindros;
        this.cilindrada = cilindrada;
        this.transmissao = transmissao;
        this.tracao = tracao;
        this.consumoCidade = consumoCidade;
        this.consumoEstrada = consumoEstrada;
        this.co2 = co2;
        this.turbo = turbo;
        this.dataRegistro = dataRegistro;
    }

    public int getId() { return this.id; }
    public String getMarca() { return this.marca; }
    public String getModelo() { return this.modelo; }
    public int getAno() { return this.ano; }
    public String getCategoria() { return this.categoria; }
    public String[] getCombustivel() { return this.combustivel; }
    public int getCilindros() { return this.cilindros; }
    public double getCilindrada() { return this.cilindrada; }
    public String getTransmissao() { return this.transmissao; }
    public String getTracao() { return this.tracao; }
    public double getConsumoCidade() { return this.consumoCidade; }
    public double getConsumoEstrada() { return this.consumoEstrada; }
    public double getCo2() { return this.co2; }
    public boolean getTurbo() { return this.turbo; }
    public Data getDataRegistro() { return this.dataRegistro; }

    public static Veiculo parseVeiculo(String s)
    {
        String[] campos = s.split(",");
        int id = Integer.parseInt(campos[0]);
        String marca = campos[1];
        String modelo = campos[2];
        int ano = Integer.parseInt(campos[3]);
        String categoria = campos[4];
        String[] combustivel = campos[5].split(";");
        int cilindros = Integer.parseInt(campos[6]);
        double cilindrada = Double.parseDouble(campos[7]);
        String transmissao = campos[8];
        String tracao = campos[9];
        double consumoCidade = Double.parseDouble(campos[10]);
        double consumoEstrada = Double.parseDouble(campos[11]);
        double co2 = Double.parseDouble(campos[12]);
        boolean turbo = Boolean.parseBoolean(campos[13]);
        Data dataRegistro = Data.parseData(campos[14]);
        return new Veiculo(id, marca, modelo, ano, categoria, combustivel, cilindros, cilindrada, transmissao, tracao, consumoCidade, consumoEstrada, co2, turbo, dataRegistro);
    }

    public String format()
    {
        String comb = "";
        for (int i = 0; i < this.combustivel.length; i++)
        {
            if (i > 0) comb += ",";
            comb += this.combustivel[i];
        }
        return String.format("[%d ## %s ## %s ## %d ## %s ## [%s] ## %d ## %.1f ## %s ## %s ## %.2f ## %.2f ## %.1f ## %b ## %s]",
            this.id, this.marca, this.modelo, this.ano, this.categoria, comb,
            this.cilindros, this.cilindrada, this.transmissao, this.tracao,
            this.consumoCidade, this.consumoEstrada, this.co2, this.turbo,
            this.dataRegistro.format());
    }
}

class LeitorCsv
{
    public static Veiculo[] ler(String caminhoArquivo)
    {
        Veiculo[] vet = new Veiculo[0];
        try
        {
            File arq = new File(caminhoArquivo);
            if (!arq.exists())
            {
                return vet;
            }
            Scanner sc = new Scanner(arq);
            if (sc.hasNextLine()) sc.nextLine();
            int n = 0;
            while (sc.hasNextLine())
            {
                sc.nextLine();
                n++;
            }
            sc.close();

            vet = new Veiculo[n];
            sc = new Scanner(arq);
            if (sc.hasNextLine()) sc.nextLine();
            int i = 0;
            while (sc.hasNextLine())
            {
                String linha = sc.nextLine();
                if (linha != null && !linha.trim().isEmpty())
                {
                    vet[i] = Veiculo.parseVeiculo(linha);
                    i++;
                }
            }
            sc.close();
        }
        catch (Exception e)
        {
            System.err.println("Erro: " + e.getMessage());
        }
        return vet;
    }
}