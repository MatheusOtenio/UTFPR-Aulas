.data 
	menu: .asciiz "Menu\n 1. Soma\n 2. Subtração\n 3. Multiplicação\n 4. Divisão\n 5. Sair\n"
	primeiro: .asciiz "Digite o primeiro número\n"
	segundo:  .asciiz "Digite o segundo número \n"
	resultado: .asciiz "Resultado: "
.text

	main:
		li $v0, 4	 #chamada de sistema
		la $a0, menu	 #informa qual o argumento
		syscall
		
		li $v0, 5
		syscall 
		move $t0, $v0
		
		li $t1, 1
		li $t2, 2
		li $t3, 3
		li $t4, 4
		
	beq $t0,$t1, soma
	beq $t0,$t2, subtracao
        beq $t0,$t3, multiplicacao
        beq $t0,$t4, divisao 
        


	
	
	
	soma:
					#imprime o txt1
		li $v0, 4
		la $a0, primeiro
		syscall
		
					#pega o primeiro número
		li $v0, 5
		syscall
		move $t0, $v0
		
					#imprime o txt2
		li $v0, 4
		la $a0, segundo
		syscall
		
					#pega o segundo número
		li $v0, 5
		syscall
		move $t1, $v0
		
					#realiza a conta
		add $t3, $t0, $t1	
		
					#imprime o txt3
		li $v0, 4
		la $a0, resultado
		syscall	
		
		li $v0, 1
		move $a0, $t3
		syscall
		
		j sair


	subtracao:
					#imprime o txt1
		li $v0, 4
		la $a0, primeiro
		syscall
		
					#pega o primeiro número
		li $v0, 5
		syscall
		move $t0, $v0
		
					#imprime o txt2
		li $v0, 4
		la $a0, segundo
		syscall
		
					#pega o segundo número
		li $v0, 5
		syscall
		move $t1, $v0
		
					#realiza a conta
		sub $t3, $t0, $t1	
		
					#imprime o txt3
		li $v0, 4
		la $a0, resultado
		syscall	
		
		li $v0, 1
		move $a0, $t3
		syscall
		
		j sair

		
	multiplicacao:
					#imprime o txt1
		li $v0, 4
		la $a0, primeiro
		syscall
		
					#pega o primeiro número
		li $v0, 5
		syscall
		move $t0, $v0
		
					#imprime o txt2
		li $v0, 4
		la $a0, segundo
		syscall
		
					#pega o segundo número
		li $v0, 5
		syscall
		move $t1, $v0
		
					#realiza a conta
		mul $t3, $t0, $t1	
		
					#imprime o txt3
		li $v0, 4
		la $a0, resultado
		syscall	
		
		li $v0, 1
		move $a0, $t3
		syscall
		
		j sair

		
	divisao:
					#imprime o txt1
		li $v0, 4
		la $a0, primeiro
		syscall
		
					#pega o primeiro número
		li $v0, 5
		syscall
		move $t0, $v0
		
					#imprime o txt2
		li $v0, 4
		la $a0, segundo
		syscall
		
					#pega o segundo número
		li $v0, 5
		syscall
		move $t1, $v0
		
					#realiza a conta
		div $t3, $t0, $t1	
		
					#imprime o txt3
		li $v0, 4
		la $a0, resultado
		syscall	
		
		li $v0,1
		move $a0, $t3
		syscall
		
		j sair
		
		
	sair: 
		li $v0, 10
		syscall
