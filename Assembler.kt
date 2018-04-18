import java.io.File

enum class Opcodes(val number:Int){
    HALT(0),
    LOADI(1),
    ADD(2),
    PUSH(3),
    POP(4),
    CMP(5),
    JMPEQ(6),
    SUB(7),
    MEMR(8),
    MEMW(9),
    JMP(10),
    NOP(11),
    MUL(12),
    CALL(13),
    RET(14),
    DIV(15),
    DBG(16),
    LOADA(17),
    LOADB(18),
    INT(19)
}

fun convertToBaseOpCode(command:String):Int{
    return when(command){
        "HALT" -> Opcodes.HALT.number
        "LOADI"-> Opcodes.LOADI.number
        "ADD" -> Opcodes.ADD.number
        "PUSH" -> Opcodes.PUSH.number
        "POP" -> Opcodes.POP.number
        "CMP" -> Opcodes.CMP.number
        "JMPEQ" -> Opcodes.JMPEQ.number
        "SUB" -> Opcodes.SUB.number
        "MEMW" -> Opcodes.MEMW.number
        "MEMR" -> Opcodes.MEMR.number
        "JMP" -> Opcodes.JMP.number
        "NOP" -> Opcodes.NOP.number
        "MUL" -> Opcodes.MUL.number
        "CALL" -> Opcodes.CALL.number
        "RET" -> Opcodes.RET.number
        "DIV" -> Opcodes.DIV.number
        "DBG" -> Opcodes.DBG.number
        "LOADA" -> Opcodes.LOADA.number
        "LOADB" -> Opcodes.LOADB.number
        "INT" -> Opcodes.INT.number
        else -> Opcodes.HALT.number
    }
}

fun padStrings(len:Int):String{
    var line = ""
    for(i in 0..len){
        line +=0
    }
    return line
}

fun twoRegisters(args:List<String>):String{
    val reg1 = args[1].split("R","")[2]
    val reg2 = args[2].split("R","")[2]
    return reg1 + reg2 + padStrings(3)
}

//region Math
fun mathOpCode(args:List<String>):String {
    val register1 = args[1].replace("R","")
    val register2 = args[2].replace("R","")
    val register3 = args[3].replace("R","")
    return  register1 + register2 + register3 + padStrings(2)
}

fun add(args:List<String>):String{
    return "02" + mathOpCode(args)
}

fun sub(args:List<String>):String{
    return "07" + mathOpCode(args)
}

fun mul(args:List<String>):String {
    return "0C" + mathOpCode(args)
}

fun div(args:List<String>):String {
    return "0F" + mathOpCode(args)
}
//endregion

fun load(args:List<String>):String{
    val register = args[1].replace("R","")
    val imm = args[2]
    val hexValue = Integer.toHexString(imm.toInt())
    return register + padStrings(4 - hexValue.length) + hexValue
}

fun loadi(args:List<String>):String {
    return "01" + load(args)
}

fun loada(args:List<String>):String{
    return "11" + load(args)
}

fun loadb(args:List<String>):String{
    return "12" + load(args)
}

fun push(arg:List<String>):String{
    return "03"+ arg[1].split("R","")[2] + padStrings(4)
}

fun pop(args:List<String>):String{
    return "04"+args[1].split("R","")[2] + padStrings(4)
}

fun cmp(args:List<String>):String{
    return "05" + twoRegisters(args)
}

fun memr(args:List<String>):String{
    return "08" + twoRegisters(args)
}
fun memw(args:List<String>):String{
    return "09" + twoRegisters(args)
}

fun jmpStuff(args:List<String>):String{
    val address = Integer.toHexString(args[1].toInt())
    return "00"+padStrings(3-address.length) + address
}

fun call(args: List<String>):String {
    return "0D" + args[1].split("R","")[2] + padStrings(4)
}

fun ret():String {
    return "0E" + padStrings(6)
}

fun jmpeq(args:List<String>):String{
    return "06"+ jmpStuff(args)
}

fun jmp(args:List<String>):String{
    return "0A"+ jmpStuff(args)
}

fun nop():String{
    return "0B" + padStrings(6)
}

fun addMore(opcode:Int, args:List<String>):String{
    return when(opcode){
        Opcodes.HALT.number -> padStrings(8)
        Opcodes.LOADI.number -> loadi(args)
        Opcodes.ADD.number -> add(args)
        Opcodes.PUSH.number -> push(args)
        Opcodes.POP.number -> pop(args)
        Opcodes.CMP.number -> cmp(args)
        Opcodes.JMPEQ.number -> jmpeq(args)
        Opcodes.SUB.number -> sub(args)
        Opcodes.MEMR.number -> memr(args)
        Opcodes.MEMW.number -> memw(args)
        Opcodes.JMP.number -> jmp(args)
        Opcodes.NOP.number -> nop()
        Opcodes.MUL.number -> mul(args)
        Opcodes.CALL.number -> call(args)
        Opcodes.RET.number -> ret()
        Opcodes.DBG.number -> "10"+padStrings(6)
        Opcodes.LOADA.number -> loada(args)
        Opcodes.LOADB.number -> loadb(args)
        else -> "0000000000"
    }
}

fun assemble(asm:List<String>):String{
    var outputString = ""
    val splittingDelims = Regex("[ \t:,]")

    for(currentLine in asm){
        val line = currentLine.replace("#","").toUpperCase().split(splittingDelims)
        val opcode = convertToBaseOpCode(line[0])
        val secondPart = addMore(opcode,line)
        outputString +=secondPart
    }
    return outputString
}

fun main(arg:Array<String>){
    var filename= "code.asm"
    if(arg.size > 1){
        filename = arg[0]
    }
    print(filename)
    val codeFile = File(filename)
    val code = codeFile.readLines()
    val output = assemble(code)
    val outputText = File("code.txt")
    outputText.writeText(output)
}
