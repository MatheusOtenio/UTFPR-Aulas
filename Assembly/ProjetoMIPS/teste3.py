
import tkinter as tk
from tkinter import filedialog, messagebox

def register_name(num):
    """Mapeia números de registradores para nomes convencionais"""
    if num == 0:
        return "$zero"
    elif num == 1:
        return "$at"
    elif 2 <= num <= 3:
        return f"$v{num-2}"
    elif 4 <= num <= 7:
        return f"$a{num-4}"
    elif 8 <= num <= 15:
        return f"$t{num-8}"
    elif 16 <= num <= 23:
        return f"$s{num-16}"
    elif 24 <= num <= 25:
        return f"$t{num-16}"
    elif 26 <= num <= 27:
        return f"$k{num-26}"
    elif num == 28:
        return "$gp"
    elif num == 29:
        return "$sp"
    elif num == 30:
        return "$fp"
    elif num == 31:
        return "$ra"
    return f"${num}"

def bin_to_assembly(bin_instr):
    if len(bin_instr) != 32:
        return "Instrução inválida (tamanho diferente de 32 bits)"
    
    opcode = bin_instr[:6]
    rs = register_name(int(bin_instr[6:11], 2))
    rt = register_name(int(bin_instr[11:16], 2))
    rd = register_name(int(bin_instr[16:21], 2))
    shamt = int(bin_instr[21:26], 2)
    funct = bin_instr[26:]
    immediate = int(bin_instr[16:], 2) if bin_instr[16] == '0' else -(65536 - int(bin_instr[16:], 2))
    address = int(bin_instr[6:], 2)
    
    try:
        # Instruções Tipo R
        if opcode == '000000':
            if funct == '100000':   # ADD
                return f"add {rd}, {rs}, {rt}"
            elif funct == '100010':  # SUB
                return f"sub {rd}, {rs}, {rt}"
            elif funct == '011000':  # MULT
                return f"mult {rs}, {rt}"
            elif funct == '100100':  # AND
                return f"and {rd}, {rs}, {rt}"
            elif funct == '100101':  # OR
                return f"or {rd}, {rs}, {rt}"
            elif funct == '000000':  # SLL
                return f"sll {rd}, {rt}, {shamt}"
            elif funct == '101010':  # SLT
                return f"slt {rd}, {rs}, {rt}"
            elif funct == '001100':  # SYSCALL
                return "syscall"
        
        # Instruções Tipo I
        elif opcode == '001000':  # ADDI
            return f"addi {rt}, {rs}, {immediate}"
        elif opcode == '001010':  # SLTI
            return f"slti {rt}, {rs}, {immediate}"
        elif opcode == '100011':  # LW
            return f"lw {rt}, {immediate}({rs})"
        elif opcode == '101011':  # SW
            return f"sw {rt}, {immediate}({rs})"
        elif opcode == '001111':  # LUI
            return f"lui {rt}, {immediate}"
        
        # Instruções Tipo J
        elif opcode == '000010':  # J
            return f"j {address}"
        
        # Chamadas de sistema (exemplo não padrão)
        elif opcode == '000001':  # IMPRIMIR INTEIRO
            return f"print_int {rt}"
        elif opcode == '000011':  # IMPRIMIR STRING
            return f"print_str {rt}"
        elif opcode == '000100':  # SAIR
            return "exit"
        
        else:
            return f"Instrução não implementada (OPCODE: {opcode})"
    
    except:
        return "Erro na tradução da instrução"

class MIPSSimulator(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Simulador MIPS Avançado")
        self.geometry("800x600")
        
        self.instructions = []
        self.current_line = 0
        self.create_widgets()
    
    def create_widgets(self):
        # Controles superiores
        control_frame = tk.Frame(self, pady=10)
        control_frame.pack(fill=tk.X)
        
        self.load_btn = tk.Button(control_frame, text="Carregar Arquivo", command=self.load_file)
        self.load_btn.pack(side=tk.LEFT, padx=5)
        
        self.step_btn = tk.Button(control_frame, text="Próximo Passo", command=self.next_step, state=tk.DISABLED)
        self.step_btn.pack(side=tk.LEFT, padx=5)
        
        # Área de código binário
        code_frame = tk.Frame(self)
        code_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)
        
        self.code_text = tk.Text(code_frame, wrap=tk.NONE, font=('Courier', 10))
        vsb = tk.Scrollbar(code_frame, command=self.code_text.yview)
        hsb = tk.Scrollbar(code_frame, orient=tk.HORIZONTAL, command=self.code_text.xview)
        self.code_text.configure(yscrollcommand=vsb.set, xscrollcommand=hsb.set)
        
        self.code_text.grid(row=0, column=0, sticky='nsew')
        vsb.grid(row=0, column=1, sticky='ns')
        hsb.grid(row=1, column=0, sticky='ew')
        
        # Painel de informações
        info_frame = tk.Frame(self)
        info_frame.pack(fill=tk.X, padx=10, pady=5)
        
        self.translation_label = tk.Label(
            info_frame, 
            text="Instrução Traduzida:",
            font=('Arial', 12, 'bold'),
            anchor=tk.W
        )
        self.translation_label.pack(fill=tk.X)
        
        self.details_label = tk.Label(
            info_frame,
            text="Detalhes da Decodificação:",
            font=('Arial', 10),
            anchor=tk.W
        )
        self.details_label.pack(fill=tk.X)
        
        # Configurar tags para realce
        self.code_text.tag_configure('current', background='yellow', foreground='black')
        self.code_text.tag_configure('executed', background='#e0e0e0')
    
    def load_file(self):
        file_path = filedialog.askopenfilename(filetypes=[("Arquivos de texto", "*.txt")])
        if not file_path:
            return
        
        try:
            with open(file_path, 'r') as file:
                self.instructions = [line.strip() for line in file]
                self.current_line = 0
                self.step_btn.config(state=tk.NORMAL)
                self.show_code()
                self.clear_highlights()
        except Exception as e:
            messagebox.showerror("Erro", f"Erro ao ler arquivo:\n{str(e)}")
    
    def show_code(self):
        self.code_text.config(state=tk.NORMAL)
        self.code_text.delete(1.0, tk.END)
        self.code_text.insert(tk.END, '\n'.join(self.instructions))
        self.code_text.config(state=tk.DISABLED)
        self.highlight_current_line()
    
    def highlight_current_line(self):
        self.code_text.tag_remove('current', 1.0, tk.END)
        if self.current_line < len(self.instructions):
            line_start = f"{self.current_line + 1}.0"
            line_end = f"{self.current_line + 1}.end"
            self.code_text.tag_add('current', line_start, line_end)
            self.code_text.see(line_start)
    
    def clear_highlights(self):
        self.code_text.tag_remove('executed', 1.0, tk.END)
    
    def next_step(self):
        if self.current_line >= len(self.instructions):
            messagebox.showinfo("Fim", "Execução concluída!")
            self.step_btn.config(state=tk.DISABLED)
            return
        
        # Obter instrução atual
        bin_instr = self.instructions[self.current_line]
        assembly = bin_to_assembly(bin_instr)
        
        # Atualizar interface
        self.translation_label.config(text=f"Instrução Traduzida: {assembly}")
        self.details_label.config(text=f"Decodificando: {bin_instr}")
        self.highlight_current_line()
        
        # Marcar linha como executada
        line_start = f"{self.current_line + 1}.0"
        line_end = f"{self.current_line + 1}.end"
        self.code_text.tag_add('executed', line_start, line_end)
        
        self.current_line += 1

if __name__ == "__main__":
    simulator = MIPSSimulator()
    simulator.mainloop()
