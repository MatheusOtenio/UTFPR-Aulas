

import java.io.*;
import java.util.*;


public class SistemaCadastroAvancado {

    // Classe Aluno
    static class Aluno {
        private static int contadorMatricula = 1;
        private String matricula;
        private String nome;
        private int idade;
        private double notaFinal;
        private String disciplina;

        public Aluno(String nome, int idade, double notaFinal, String disciplina) {
            this.matricula = "MAT" + (contadorMatricula++);
            this.nome = nome;
            this.idade = idade;
            this.notaFinal = notaFinal;
            this.disciplina = disciplina;
        }

        public String getMatricula() {
            return matricula;
        }

        public String getNome() {
            return nome;
        }

        public void setNome(String nome) {
            this.nome = nome;
        }

        public void setIdade(int idade) {
            this.idade = idade;
        }

        public void setNotaFinal(double notaFinal) {
            this.notaFinal = notaFinal;
        }

        public void setDisciplina(String disciplina) {
            this.disciplina = disciplina;
        }

        public String getInfo() {
            return "Matrícula: " + matricula + ", Nome: " + nome + ", Idade: " + idade +
                   ", Nota Final: " + notaFinal + ", Disciplina: " + disciplina;
        }

        public boolean isAprovado() {
            return notaFinal >= 7.0;
        }
    }

    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Aluno> alunos = carregarDados(); // Lê dados do arquivo ao iniciar
        int opcao;

        do {
            System.out.println("\nMenu:");
            System.out.println("1. Adicionar Aluno");
            System.out.println("2. Listar Alunos");
            System.out.println("3. Calcular Média das Notas");
            System.out.println("4. Editar Aluno");
            System.out.println("5. Remover Aluno");
            System.out.println("6. Relatórios");
            System.out.println("7. Sair");
            System.out.print("Escolha uma opção: ");
            opcao = scanner.nextInt();
            scanner.nextLine(); // Limpar o buffer

            switch (opcao) {
                    
                case 1:
                    System.out.print("Nome do Aluno: ");
                    String nome = scanner.nextLine();
                    System.out.print("Idade do Aluno: ");
                    int idade = scanner.nextInt();
                    System.out.print("Nota Final do Aluno: ");
                    double notaFinal = scanner.nextDouble();
                    scanner.nextLine(); // Limpar o buffer
                    System.out.print("Disciplina: ");
                    String disciplina = scanner.nextLine();

                    if (nome.isEmpty() || idade < 0 || notaFinal < 0 || notaFinal > 10) {
                        System.out.println("Entrada inválida. Verifique os dados.");
                    } else {
                        alunos.add(new Aluno(nome, idade, notaFinal, disciplina));
                        System.out.println("Aluno adicionado com sucesso!");
                    }
                    break;

                case 2:
                    if (alunos.isEmpty()) {
                        System.out.println("Nenhum aluno cadastrado.");
                    } else {
                        System.out.println("\nLista de Alunos:");
                        for (Aluno aluno : alunos) {
                            System.out.println(aluno.getInfo());
                        }
                    }
                    break;

                case 3:
                    if (alunos.isEmpty()) {
                        System.out.println("Nenhuma nota para calcular.");
                    } else {
                        double soma = 0;
                        for (Aluno aluno : alunos) {
                            soma += aluno.notaFinal;
                        }
                        System.out.println("Média das Notas: " + (soma / alunos.size()));
                    }
                    break;

                case 4:
                    System.out.print("Informe a matrícula do aluno a ser editado: ");
                    String matriculaEdit = scanner.nextLine();
                    Aluno alunoEdit = buscarAlunoPorMatricula(alunos, matriculaEdit);

                    if (alunoEdit == null) {
                        System.out.println("Aluno não encontrado.");
                    } else {
                        System.out.print("Novo Nome (ou Enter para não alterar): ");
                        String novoNome = scanner.nextLine();
                        if (!novoNome.isEmpty()) alunoEdit.setNome(novoNome);

                        System.out.print("Nova Idade (ou -1 para não alterar): ");
                        int novaIdade = scanner.nextInt();
                        if (novaIdade >= 0) alunoEdit.setIdade(novaIdade);

                        System.out.print("Nova Nota Final (ou -1 para não alterar): ");
                        double novaNota = scanner.nextDouble();
                        if (novaNota >= 0 && novaNota <= 10) alunoEdit.setNotaFinal(novaNota);

                        scanner.nextLine(); // Limpar o buffer
                        System.out.print("Nova Disciplina (ou Enter para não alterar): ");
                        String novaDisciplina = scanner.nextLine();
                        if (!novaDisciplina.isEmpty()) alunoEdit.setDisciplina(novaDisciplina);

                        System.out.println("Aluno atualizado com sucesso!");
                    }
                    break;

                case 5:
                    System.out.print("Informe a matrícula do aluno a ser removido: ");
                    String matriculaRemover = scanner.nextLine();
                    Aluno alunoRemover = buscarAlunoPorMatricula(alunos, matriculaRemover);

                    if (alunoRemover == null) {
                        System.out.println("Aluno não encontrado.");
                    } else {
                        alunos.remove(alunoRemover);
                        System.out.println("Aluno removido com sucesso!");
                    }
                    break;

                case 6:
                    System.out.println("\nRelatórios:");
                    System.out.println("1. Alunos Aprovados");
                    System.out.println("2. Alunos Reprovados");
                    System.out.println("3. Alunos em Ordem Alfabética");
                    System.out.print("Escolha uma opção: ");
                    int relatorioOpcao = scanner.nextInt();
                    scanner.nextLine();

                    if (relatorioOpcao == 1) {
                        System.out.println("\nAlunos Aprovados:");
                        for (Aluno aluno : alunos) {
                            if (aluno.isAprovado()) {
                                System.out.println(aluno.getInfo());
                            }
                        }
                    } else if (relatorioOpcao == 2) {
                        System.out.println("\nAlunos Reprovados:");
                        for (Aluno aluno : alunos) {
                            if (!aluno.isAprovado()) {
                                System.out.println(aluno.getInfo());
                            }
                        }
                    } else if (relatorioOpcao == 3) {
                        alunos.sort(Comparator.comparing(Aluno::getNome));
                        System.out.println("\nAlunos em Ordem Alfabética:");
                        for (Aluno aluno : alunos) {
                            System.out.println(aluno.getInfo());
                        }
                    } else {
                        System.out.println("Opção inválida.");
                    }
                    break;

                case 7:
                    salvarDados(alunos); // Salva dados no arquivo ao sair
                    System.out.println("Encerrando o sistema...");
                    break;

                default:
                    System.out.println("Opção inválida. Tente novamente.");
            }
        } while (opcao != 7);

        scanner.close();
    }

    // Método para buscar aluno por matrícula
    private static Aluno buscarAlunoPorMatricula(ArrayList<Aluno> alunos, String matricula) {
        for (Aluno aluno : alunos) {
            if (aluno.getMatricula().equals(matricula)) {
                return aluno;
            }
        }
        return null;
    }

    
    // Métodos para salvar e carregar dados em arquivo
    private static void salvarDados(ArrayList<Aluno> alunos) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("alunos.txt"))) {
            for (Aluno aluno : alunos) {
                writer.write(aluno.getMatricula() + ";" + aluno.getNome() + ";" +
                             aluno.idade + ";" + aluno.notaFinal + ";" + aluno.disciplina + "\n");
            }
        }
    }

    
    private static ArrayList<Aluno> carregarDados() throws IOException {
        ArrayList<Aluno> alunos = new ArrayList<>();
        File file = new File("alunos.txt");
        if (file.exists()) {
            try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                String linha;
                while ((linha = reader.readLine()) != null) {
                    String[] dados = linha.split(";");
                    alunos.add(new Aluno(dados[1], Integer.parseInt(dados[2]),
                            Double.parseDouble(dados[3]), dados[4]));
                }
            }
        }
        
        return alunos;
    }
}
