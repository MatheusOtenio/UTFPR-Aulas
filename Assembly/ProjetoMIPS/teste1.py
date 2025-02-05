import tkinter as tk
from tkinter import messagebox
import sys

class MIPS:
    def __init__(self):
        self.reg = [0] * 32  # Registradores $0-$31
        self.pc = 0x00400000  # Contador de programa
        self.hi = 0
        self.lo = 0
        self.data_mem = {}  # Memória de dados (endereço byte)
        self.instr_mem = []  # Memória de instruções
        self.output = []     # Saídas do sistema

    def load_program(self, filename):
        try:
            with open(filename, 'r') as f:
                self.instr_mem = [line.strip() for line in f if len(line.strip()) == 32]
        except FileNotFoundError:
            messagebox.showerror("Erro", "Arquivo não encontrado.")

    def get_current_instr(self):
        index = (self.pc - 0x00400000) // 4
        return self.instr_mem[index] if 0 <= index < len(self.instr_mem) else None

    def to_signed(self, value):
        return value if value < 0x80000000 else value - 0x100000000

    def step(self):
        instr = self.get_current_instr()
        if not instr:
            return False

        opcode = instr[:6]
        self.output.clear()

        # Decodificação R-type
        if opcode == '000000':
            rs = int(instr[6:11], 2)
            rt = int(instr[11:16], 2)
            rd = int(instr[16:21], 2)
            shamt = int(instr[21:26], 2)
            funct = instr[26:32]

            if funct == '100000':  # ADD
                self.reg[rd] = (self.reg[rs] + self.reg[rt]) & 0xFFFFFFFF
            elif funct == '100010':  # SUB
                self.reg[rd] = (self.reg[rs] - self.reg[rt]) & 0xFFFFFFFF
            elif funct == '011000':  # MULT
                a = self.to_signed(self.reg[rs])
                b = self.to_signed(self.reg[rt])
                res = a * b
                self.hi = (res >> 32) & 0xFFFFFFFF
                self.lo = res & 0xFFFFFFFF
            elif funct == '100100':  # AND
                self.reg[rd] = self.reg[rs] & self.reg[rt]
            elif funct == '100101':  # OR
                self.reg[rd] = self.reg[rs] | self.reg[rt]
            elif funct == '000000':  # SLL
                self.reg[rd] = (self.reg[rt] << shamt) & 0xFFFFFFFF
            elif funct == '101010':  # SLT
                a = self.to_signed(self.reg[rs])
                b = self.to_signed(self.reg[rt])
                self.reg[rd] = 1 if a < b else 0
            elif funct == '001100':  # SYSCALL
                v0 = self.reg[2]
                if v0 == 1:
                    self.output.append(str(self.reg[4]))
                elif v0 == 4:
                    addr = self.reg[4]
                    s = ''
                    while True:
                        byte = self.data_mem.get(addr, 0)
                        if byte == 0:
                            break
                        s += chr(byte)
                        addr += 1
                    self.output.append(s)
                elif v0 == 10:
                    return False

        # Decodificação I-type
        else:
            rs = int(instr[6:11], 2)
            rt = int(instr[11:16], 2)
            imm = int(instr[16:32], 2)
            imm_signed = imm if imm < 32768 else imm - 65536  # Sign extend

            if opcode == '001000':  # ADDI
                self.reg[rt] = (self.reg[rs] + imm_signed) & 0xFFFFFFFF
            elif opcode == '100011':  # LW
                addr = self.reg[rs] + imm_signed
                val = 0
                for i in range(4):
                    val = (val << 8) | self.data_mem.get(addr + i, 0)
                self.reg[rt] = val
            elif opcode == '101011':  # SW
                addr = self.reg[rs] + imm_signed
                val = self.reg[rt]
                for i in range(4):
                    self.data_mem[addr + i] = (val >> (24 - 8 * i)) & 0xFF
            elif opcode == '001010':  # SLTI
                a = self.to_signed(self.reg[rs])
                b = imm_signed
                self.reg[rt] = 1 if a < b else 0
            elif opcode == '001111':  # LUI
                self.reg[rt] = (imm << 16) & 0xFFFFFFFF

        self.pc += 4
        return True

class MIPSGUI:
    def __init__(self, root):
        self.root = root
        self.mips = MIPS()
        self.setup_gui()

    def setup_gui(self):
        self.root.title("Simulador MIPS")
        self.reg_frame = tk.Frame(self.root)
        self.reg_frame.pack()

        self.reg_labels = []
        for i in range(32):
            label = tk.Label(self.reg_frame, text=f"${i}: 0x{0:08x}", width=15)
            label.grid(row=i//8, column=i%8)
            self.reg_labels.append(label)

        self.control_frame = tk.Frame(self.root)
        self.control_frame.pack()
        self.step_btn = tk.Button(self.control_frame, text="Passo", command=self.step)
        self.step_btn.pack(side=tk.LEFT)
        self.run_btn = tk.Button(self.control_frame, text="Executar", command=self.run)
        self.run_btn.pack(side=tk.LEFT)
        self.load_btn = tk.Button(self.control_frame, text="Carregar Programa", command=self.load_program)
        self.load_btn.pack(side=tk.LEFT)

        self.console = tk.Text(self.root, height=10, state=tk.DISABLED)
        self.console.pack()

    def load_program(self):
        filename = tk.filedialog.askopenfilename()
        if filename:
            self.mips.load_program(filename)
            self.update_display()

    def update_display(self):
        for i in range(32):
            self.reg_labels[i].config(text=f"${i}: 0x{self.mips.reg[i]:08x}")

        for msg in self.mips.output:
            self.console.insert(tk.END, msg + '\n')
        self.console.see(tk.END)

    def step(self):
        if self.mips.step():
            self.update_display()
        else:
            messagebox.showinfo("Fim", "Execução concluída.")
            self.generate_report()

    def run(self):
        def auto_step():
            if self.mips.step():
                self.update_display()
                self.root.after(100, auto_step)
            else:
                messagebox.showinfo("Fim", "Execução concluída.")
                self.generate_report()
        auto_step()

    def generate_report(self):
        with open("registradores.txt", "w") as f:
            f.write("Registradores:\n")
            for i in range(32):
                f.write(f"${i}: 0x{self.mips.reg[i]:08x}\n")
            f.write(f"HI: 0x{self.mips.hi:08x}\n")
            f.write(f"LO: 0x{self.mips.lo:08x}\n")

if __name__ == "__main__":
    root = tk.Tk()
    gui = MIPSGUI(root)
    root.mainloop()