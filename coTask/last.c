.data :

	Menu :          	.asciiz  "\n\n0- Enter Requests\n1- Search about Request\n2- Search about priority \n3- Search about Request with Priority \n4- Delete All requests with specific priority \n5- Process All requests with specific priority \n6- Empty All Lists\n(-1) To Exit\n\nYour Choice:   "
	Entering_Req : 		.asciiz  "Enter Number of requests that you have (maximum 80 requests):  "
	Entering_Pr_toDelete:  	.asciiz "Enter the priority which you want to delete their contents :   "
	Entering_Pr_toProcess: 	.asciiz "Enter the priority that you want to process their requests :   "
	invalid_task: 	.asciiz 	"\nYou entered an invalid number... try again:  "
	Enter_Requests:	.asciiz 	"\nEnter your request: "
	No_Space:	.asciiz		"There is no enough space in the arrays"
	All_empty: 	.asciiz        "All lists are empty now."
	already_empty: 	.asciiz	       "The list is already empty\n"
	del_success: 	.asciiz	       "List deleted successfully\n"
	invalid_list: 	.asciiz	       "\nYou Entered an invalid list number please\n "
	process_empty:	.asciiz		"There's no requests here the list is empty\n"
	separator:	.asciiz 	"-----------------------------------------------\n"
	Size: 		.word 		5
	Dones: 		.asciiz 	"Done"
	enter: 		.byte		'\n'

	critical:	.space 	20
	high:		.space 	20
	medium:		.space 	20
	low:		.space 	20

	criticalSize:	.word   0
	highSize:	.word	0
	mediumSize:	.word	0
	lowSize:	.word	0

.text
.globl main
	main:
		li $t9 , 0 #load imidiate t9 to 0 and this for task
		li $t8 , 0 #load imidiate t8 to 0 and this for priority
		li $t7 , 0 #load imidiate t7 to 0 and this for numberOfRequests
		li $t0 , -1

		lw $s0 , Size
		lw $s1 , criticalSize
		lw $s2 , highSize
		lw $s3 , mediumSize
		lw $s4 , lowSize
		#li $v0, 4     #command for printing a string
    		#la $a0, Menu #loading the string to print into the argument to enable printing
    		#syscall

  		#li $v0 , 5
		#syscall
		#move $t9 , $v0

	WhileLoop: 	beq $t9 , $t0 , DoneWhileLoop
			li $v0, 4     #command for printing a string
    			la $a0, Menu #loading the string to print into the argument to enable printing
    			syscall

			li $v0 , 5
			syscall
			move $t9 , $v0

	 		addi $s5 , $zero , 0
	 		bne $t9 , $s5 , CASE1_COND
	 		j CASE0_BODY
	 	CASE1_COND: addi $s5 , $zero , 1
	 		    bne $t9 , $s5 , CASE2_COND
	 		    j CASE1_BODY
	 	CASE2_COND: addi $s5 , $zero , 2
	 		    bne $t9 , $s5 , CASE3_COND
	 		    j CASE2_BODY
	 	CASE3_COND: addi $s5 , $zero , 3
	 		    bne $t9 , $s5 , CASE4_COND
	 		    j CASE3_BODY
	 	CASE4_COND: addi $s5 , $zero , 4
	 		    bne $t9 , $s5 , CASE5_COND
	 		    j CASE4_BODY
	 	CASE5_COND: addi $s5 , $zero , 5
	 		    bne $t9 , $s5 , CASE6_COND
	 		    j CASE5_BODY
	 	CASE6_COND: addi $s5 , $zero , 6
	 		    bne $t9 , $s5 , CASEMINUS1_COND
	 		    j CASE6_BODY
	 	CASEMINUS1_COND: addi $s5 , $zero , -1
	 		    bne $t9 , $s5 , DEFAULTCASE_COND
	 		    j CASEMINUS1_BODY
	 	DEFAULTCASE_COND:
	 		    li $v0 , 4
	 		    la $a0 , invalid_task
	 		    syscall
	 		    j EXIT_MAIN_SWITCH

	 	CASE0_BODY:
	 		li $v0, 4     #command for printing a string
    			la $a0, Entering_Req #loading the string to print into the argument to enable printing
    			syscall
    			# Scan number of requests and save it in $t7 register
    			li $v0 , 5
    			syscall
    			move $t7 , $v0

    			#initialize the counter of the for loop $t1
    			addi $t1 , $zero , 0

    			#loop to scan the requets from the user
    			Scan_Loop: beq $t1 , $t7 , After_Scan_Loop

    			addi $a0 , $zero , 0

    			li $v0 , 4
    			la $a0 , Enter_Requests
    			syscall

	 		# Scan char form user and save it in $a2
	 		li $v0 , 12
	 		syscall
	 		move $a2 , $v0

	 		#call the storeRequest function
	 		jal storeRequest

	 		#increment the for loop conter
	 		addi $t1 , $t1 ,1
	 		j Scan_Loop

	 	After_Scan_Loop:

	 		#sort critical
	 		sgt $t5 , $s1 , $zero
	 		ble $s1 , $zero , sortHigh
	 			la   $a0 , critical
	 			li   $a1 , 0
	 			move $a2 , $s1
	 			addi $a2 , $a2 , -1
	 			jal QUICK
	 	sortHigh:
	 		sgt $t5 , $s2 , $zero
	 		beqz $t5 , sortMed
	 			la   $a0 , high
	 			li   $a1 , 0
	 			move $a2 , $s2
	 			addi $a2 , $a2 , -1
	 			jal QUICK

	 	sortMed:
	 		sgt $t5 , $s2 , $zero
	 		beqz $t5 , sortLow
	 			la   $a0 , medium
	 			li   $a1 , 0
	 			move $a2 , $s3
	 			addi $a2 , $a2 , -1
	 			jal QUICK


	 	sortLow:
	 		sgt $t5 , $s2 , $zero
	 		beqz $t5 , EXIT_MAIN_SWITCH
	 			la   $a0 , low
	 			li   $a1 , 0
	 			move $a2 , $s4
	 			addi $a2 , $a2 , -1
	 			jal QUICK


		j EXIT_MAIN_SWITCH

	    	CASE1_BODY:
	    	CASE2_BODY:
	    	CASE3_BODY:

	    		addi $t1 , $zero , 0
	    		addi $t2 , $zero , 1

	    		lb $t3 , critical($t1)
	    		lb $t4 , critical($t2)
	    		slt  $t5 , $t3 , $t4

	    		li $v0 , 1
	    		move $a0 , $t5
	    		syscall

	    	CASE4_BODY:
	    		# print to user to enter the recuired priority
	    		li $v0 , 4
	    		la $a0 , Entering_Pr_toDelete
	    		syscall

	    		#scan the priority number form the user
	    		li $v0 , 5
	    		syscall
	    		move $a2 , $v0

	    		jal deleteRequestWithSpecificPriority

			j EXIT_MAIN_SWITCH


	    	CASE5_BODY:
	    		# print to user to enter the recuired priority
	    		li $v0 , 4
	    		la $a0 , Entering_Pr_toProcess
	    		syscall

	    		#scan the priority number form the user
	    		li $v0 , 5
	    		syscall
	    		move $a2 , $v0

	    		jal processAllRequestsWithSpecificPriority

			j EXIT_MAIN_SWITCH

	    	CASE6_BODY:
	    		jal emptyAllLists
	    		j EXIT_MAIN_SWITCH

	    	CASEMINUS1_BODY:
	 		    j DoneWhileLoop

	 	EXIT_MAIN_SWITCH:
	 		    j WhileLoop

	DoneWhileLoop:
		li , $v0 , 10
		syscall

#----------------------End of The Main Procedure------------------------


#---------------------Store Request Procedure----------------------------
	storeRequest:
		#initialize the counter of the for Array of chars $t2
    			addi $t2 , $zero , 0
		beq $s1 , $s0  , AddToHighArray
			add $t2 , $zero , $s1
			#save the char to the memory and increment the index
	 		sb $a2 , critical($t2)
	 		#increment the sizeVariable of the array
	 		addi $s1 , $s1 , 1
	 		jr $ra
	 	AddToHighArray:
	 		beq $s2 , $s0  , AddToMedArray
			add $t2 , $zero , $s2
			#save the char to the memory and increment the index
	 		sb $a2 , high($t2)
	 		#increment the sizeVariable of the array
	 		addi $s2 , $s2 , 1
	 		jr $ra
	 	AddToMedArray:
	 		beq $s3 , $s0  , AddToLowArray
			add $t2 , $zero , $s3
			#save the char to the memory and increment the index
	 		sb $a2 , medium($t2)
	 		#increment the sizeVariable of the array
	 		addi $s3 , $s3 , 1
	 		jr $ra
	 	AddToLowArray:
			beq $s4 , $s0  , storeRequestExit
			add $t2 , $zero , $s4
			#save the char to the memory and increment the index
	 		sb $a2 , low($t2)
	 		#increment the sizeVariable of the array
	 		addi $s4 , $s4 , 1
	 		jr $ra
		storeRequestExit:
			li $v0 , 4
			la $a0 , No_Space
			syscall
			jr $ra

#--------------------End Of Store Request Procedure------------------



#--------------------Process All Request Procedure-------------------
	processAllRequestsWithSpecificPriority:

		addi $sp , $sp , -4 # save the return value of the main procedure because of the nested procedures
		sw   $ra , 0($sp)

		addi $s5 , $zero , 1	#add one to $s5 to switch the argument case
		bne $a2 , $s5 , processCASE2_COND
	 		add $a3 , $zero , $s1 	#save the array size to $a3
	 		beqz $a3 , processEmptyMessage	#if $a3 = 0 so the array is empty
	 		la   $a2 , critical	#save the base index of the array in $a2
				jal printList	#call printList procedure
				addi $s1 , $zero , 0	#make the array counter = 0
				j endProcessAndBackToMain	#jump to the endProcessAndBackToMain
		processCASE2_COND: addi $s5 , $zero , 2
	 		    bne $a2 , $s5 , processCASE3_COND
	 		    add $a3 , $zero , $s2
	 		    beqz $a3 , processEmptyMessage
	 		    la   $a2 , high
				jal printList
				addi $s2 , $zero , 0
				j endProcessAndBackToMain
	 	processCASE3_COND: addi $s5 , $zero , 3
	 		    bne $a2 , $s5 , processCASE4_COND
	 		    add $a3 , $zero , $s3
	 		    beqz $a3 , processEmptyMessage
	 		    la   $a2 , medium
				jal printList
				addi $s3 , $zero , 0
				j endProcessAndBackToMain
	 	processCASE4_COND: addi $s5 , $zero , 4
	 		    bne $a2 , $s5 , processDEFAULTCASE_COND
	 		    add $a3 , $zero , $s4
	 		    beqz $a3 , processEmptyMessage
	 		    la   $a2 , low
			    	jal printList
			    	addi $s4 , $zero , 0
				j endProcessAndBackToMain

		processDEFAULTCASE_COND:
			li $v0 , 4
			la $a0 , invalid_list
			syscall
			lw $ra , 0($sp)	#restore (pop) the return address of the main from the stack
			addi $sp , $sp , 4	#restore the stack pointer
			j CASE5_BODY

		processEmptyMessage:
			li $v0 , 4
			la $a0 , process_empty
			syscall
			j endProcessAndBackToMain

		endProcessAndBackToMain:
			lw $ra , 0($sp)	#restore (pop) the return address of the main from the stack
			addi $sp , $sp , 4	#restore the stack pointer
			jr $ra

#--------------------End of Process All Request Procedure-------------------


#--------------------Print List Procedure------------------------
	printList:
		addi $t2 , $zero , 0
		move $t3 , $a2

		li $v0 , 4
    		la $a0 , separator
    		syscall

		process_Loop: beq $t2 , $a3 , EXIT_process_Loop

    		addi $a0 , $zero , 0



    		li $v0 , 11
    		lb $a0 , 0($t3)
    		syscall

    		li $v0 , 11
    		lb $a0 , enter
    		syscall

	 	#increment the for loop conter
	 	addi $t2 , $t2 ,1
		addi $t3 , $t3 ,1
	 	j process_Loop

		EXIT_process_Loop:

			li $v0 , 4
    			la $a0 , separator
    			syscall

			jr $ra

#------------------End of Print List Procedure--------------

#------------------Empty all Lists Procedure--------------

	emptyAllLists:
		addi $s1 , $zero , 0
		addi $s2 , $zero , 0
		addi $s3 , $zero , 0
		addi $s4 , $zero , 0

		li $v0 , 4
		la $a0 , All_empty
		syscall

		jr $ra
#------------------End of Empty all Lists Procedure--------------

#-----------------Delete Request Procedure---------------

	deleteRequestWithSpecificPriority:
		addi $s5 , $zero , 1	#add one to $s5 to switch the argument case
		bne $a2 , $s5 , deleteCASE2_COND
	 		beqz $s1 , ListAlreadyEmptyMessage	#if $a3 = 0 so the array is  already empty
			addi $s1 , $zero , 0	#make the array counter = 0
			j listDeletedSuccessfullyMessage
		deleteCASE2_COND:
				addi $s5 , $zero , 2
				bne $a2 , $s5 , deleteCASE3_COND
				beqz $s2 , ListAlreadyEmptyMessage
				addi $s2 , $zero , 0
				j listDeletedSuccessfullyMessage
	 	deleteCASE3_COND:
				addi $s5 , $zero , 3
				bne $a2 , $s5 , deleteCASE4_COND
				beqz $s3 , ListAlreadyEmptyMessage
				addi $s3 , $zero , 0
				j listDeletedSuccessfullyMessage
	 	deleteCASE4_COND:
				addi $s5 , $zero , 4
				bne $a2 , $s5 , deleteDEFAULTCASE_COND
				beqz $s4 , ListAlreadyEmptyMessage
			    	addi $s4 , $zero , 0
				j endProcessAndBackToMain

		deleteDEFAULTCASE_COND:
				li $v0 , 4
				la $a0 , invalid_list
				syscall
				j CASE4_BODY

		ListAlreadyEmptyMessage:
				li $v0 , 4
				la $a0 , already_empty
				syscall
				jr $ra

		listDeletedSuccessfullyMessage:
				li $v0 , 4
				la $a0 , del_success
				syscall
				jr $ra

#---------------------End of Delete List Procedure-----------------------

#---------------------Quicksort Procedure------------------


QUICK:
## quick sort

# store $s and $ra
	addi	$sp, $sp, -24	# Adjest sp
	sw		$s0, 0($sp)		# store s0
	sw		$s1, 4($sp)		# store s1
	sw		$s2, 8($sp)		# store s2
	sw		$a1, 12($sp)	# store a1
	sw		$a2, 16($sp)	# store a2
	sw		$ra, 20($sp)	# store ra

# set $s
	move	$s0, $a1		# l = left
	move	$s1, $a2		# r = right
	move	$s2, $a1		# p = left

# while (l < r)
Loop_quick1:
	bge		$s0, $s1, Loop_quick1_done

# while (arr[l] <= arr[p] && l < right)
Loop_quick1_1:
	li		$t7, 1		# t7 = 1
	# t0 = &arr[l]
	mult	$s0, $t7
	mflo	$t0				# t0 =  l * 4bit
	add		$t0, $t0, $a0	# t0 = &arr[l]
	lb		$t0, 0($t0)
	# t1 = &arr[p]
	mult	$s2, $t7
	mflo	$t1				# t1 =  p * 4bit
	add		$t1, $t1, $a0	# t1 = &arr[p]
	lb		$t1, 0($t1)
	# check arr[l] <= arr[p]
	bgt		$t0, $t1, Loop_quick1_1_done
	# check l < right
	bge		$s0, $a2, Loop_quick1_1_done
	# l++
	addi	$s0, $s0, 1
	j		Loop_quick1_1

Loop_quick1_1_done:

# while (arr[r] >= arr[p] && r > left)
Loop_quick1_2:
	li		$t7, 1			# t7 = 4
	# t0 = &arr[r]
	mult	$s1, $t7
	mflo	$t0				# t0 =  r * 4bit
	add		$t0, $t0, $a0	# t0 = &arr[r]
	lb		$t0, 0($t0)
	# t1 = &arr[p]
	mult	$s2, $t7
	mflo	$t1				# t1 =  p * 4bit
	add		$t1, $t1, $a0	# t1 = &arr[p]
	lb		$t1, 0($t1)
	# check arr[r] >= arr[p]
	blt		$t0, $t1, Loop_quick1_2_done
	# check r > left
	ble		$s1, $a1, Loop_quick1_2_done
	# r--
	addi	$s1, $s1, -1
	j		Loop_quick1_2

Loop_quick1_2_done:

# if (l >= r)
	blt		$s0, $s1, If_quick1_jump
# SWAP (arr[p], arr[r])
	li		$t7, 1		# t7 = 4
	# t0 = &arr[p]
	mult	$s2, $t7
	mflo	$t6				# t6 =  p * 4bit
	add		$t0, $t6, $a0	# t0 = &arr[p]
	# t1 = &arr[r]
	mult	$s1, $t7
	mflo	$t6				# t6 =  r * 4bit
	add		$t1, $t6, $a0	# t1 = &arr[r]
	# Swap
	lb		$t2, 0($t0)
	lb		$t3, 0($t1)
	sb		$t3, 0($t0)
	sb		$t2, 0($t1)

# quick(arr, left, r - 1)
	# set arguments
	move	$a2, $s1
	addi	$a2, $a2, -1	# a2 = r - 1
	jal		QUICK
	# pop stack
	lw		$a1, 12($sp)	# load a1
	lw		$a2, 16($sp)	# load a2
	lw		$ra, 20($sp)	# load ra

# quick(arr, r + 1, right)
	# set arguments
	move	$a1, $s1
	addi	$a1, $a1, 1		# a1 = r + 1
	jal		QUICK
	# pop stack
	lw		$a1, 12($sp)	# load a1
	lw		$a2, 16($sp)	# load a2
	lw		$ra, 20($sp)	# load ra

# return
	lw		$s0, 0($sp)		# load s0
	lw		$s1, 4($sp)		# load s1
	lw		$s2, 8($sp)		# load s2
	addi	$sp, $sp, 24	# Adjest sp
	jr		$ra

If_quick1_jump:

# SWAP (arr[l], arr[r])
	li		$t7, 1		# t7 = 4
	# t0 = &arr[l]
	mult	$s0, $t7
	mflo	$t6				# t6 =  l * 4bit
	add		$t0, $t6, $a0	# t0 = &arr[l]
	# t1 = &arr[r]
	mult	$s1, $t7
	mflo	$t6				# t6 =  r * 4bit
	add		$t1, $t6, $a0	# t1 = &arr[r]
	# Swap
	lb		$t2, 0($t0)
	lb		$t3, 0($t1)
	sb		$t3, 0($t0)
	sb		$t2, 0($t1)

	j		Loop_quick1

Loop_quick1_done:

# return

	lw		$s0, 0($sp)		# load s0
	lw		$s1, 4($sp)		# load s1
	lw		$s2, 8($sp)		# load s2
	addi	$sp, $sp, 24	# Adjest sp
	jr		$ra

#------------------------- End Of Delete Procedure------------------------


