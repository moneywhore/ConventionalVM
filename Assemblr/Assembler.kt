import java.io.File

enum class OpCodes(val number:Int){
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
    INT(19),
    PUSHL(20),
    SINC(21),
    SDEC(22),
    RCUR(23),
    WCUR(24)
}

fun convertToBaseOpCode(command:String):Int{
    return when(command){
        "HALT" -> OpCodes.HALT.number
        "LOADI"-> OpCodes.LOADI.number
        "ADD" -> OpCodes.ADD.number
        "PUSH" -> OpCodes.PUSH.number
        "POP" -> OpCodes.POP.number
        "CMP" -> OpCodes.CMP.number
        "JMPEQ" -> OpCodes.JMPEQ.number
        "SUB" -> OpCodes.SUB.number
        "MEMW" -> OpCodes.MEMW.number
        "MEMR" -> OpCodes.MEMR.number
        "JMP" -> OpCodes.JMP.number
        "NOP" -> OpCodes.NOP.number
        "MUL" -> OpCodes.MUL.number
        "CALL" -> OpCodes.CALL.number
        "RET" -> OpCodes.RET.number
        "DIV" -> OpCodes.DIV.number
        "DBG" -> OpCodes.DBG.number
        "LOADA" -> OpCodes.LOADA.number
        "LOADB" -> OpCodes.LOADB.number
        "INT" -> OpCodes.INT.number
        "PUSHL" -> OpCodes.PUSHL.number
        "SINC" -> OpCodes.SINC.number
        "SDEC" -> OpCodes.SDEC.number
        "RCUR" -> OpCodes.RCUR.number
        "WCUR" -> OpCodes.WCUR.number
        else -> OpCodes.HALT.number
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

fun mathOpCode(args:List<String>):String {
    val register1 = args[1].replace("R","")
    val register2 = args[2].replace("R","")
    val register3 = args[3].replace("R","")
    return  register1 + register2 + register3 + padStrings(2)
}


fun loadi(args:List<String>):String {
    val register = args[1].replace("R","")
    var imm = args[2]
    if (args[2].startsWith("%")) {
        imm = imm.replace("%", "")
        return "01" + register + padStrings(4 - imm.length) + imm
    }
    val hexValue = Integer.toHexString(imm.toInt())
    return "01" + register + padStrings(4 - hexValue.length) + hexValue
}

fun loada(args: List<String>):String {
    val register = args[1].replace("R", "")
    var imm = args[2]
    if (args[2].startsWith("%")) {
        imm = imm.replace("%", "")
        return "11" + register + padStrings(4 - imm.length) + imm
    }
    val hexValue = Integer.toHexString(imm.toInt())
    return "11" + register + padStrings(4 - hexValue.length) + hexValue
}

fun loadb(args: List<String>):String {
    val register = args[1].replace("R", "")
    var imm = args[2]
    if (args[2].startsWith("%")) {
        imm = imm.replace("%", "")
        return "12" + register + padStrings(4 - imm.length) + imm
    }
    val hexValue = Integer.toHexString(imm.toInt())
    return "12" + register + padStrings(4 - hexValue.length) + hexValue
}

fun dbg():String {
    return "10" + padStrings(6)
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

fun push(arg:List<String>):String{
    return "03"+ arg[1].split("R","")[2] + padStrings(4)
}

fun pushl(args: List<String>):String {
    return "14" + jmpStuff(args)
}

fun pop(args:List<String>):String{
    return "04"+args[1].split("R","")[2] + padStrings(4)
}

fun stackInc(args:List<String>):String {
    return "15" + jmpStuff(args)
}

fun stackDec(args:List<String>):String {
    return "16" + jmpStuff(args)
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

fun rcur(args: List<String>):String {
    return("17" + args[1].split("R","")[2] + padStrings(4))
}

fun wcur(args: List<String>):String {
    return("18" + args[1].split("R","")[2] + padStrings(4))
}

fun jmpStuff(args:List<String>):String{
    var address = args[1]
    if (args[1].startsWith("%")) {
        address = address.replace("%", "")
        return "00" + padStrings(3 - address.length) + address
    }
    address = Integer.toHexString(address.toInt())
    return "00"+padStrings(3-address.length) + address
}

fun call(args: List<String>):String {
    return "0D" + args[1].split("R","")[2] + padStrings(4)
}

fun ret():String {
    return "0E" + padStrings(5)
}

fun jmpeq(args:List<String>):String{
    return "06"+ jmpStuff(args)
}

fun jmp(args:List<String>):String{
    return "0A"+ jmpStuff(args)
}

fun nop():String{
    return "0B" + padStrings(5)
}

fun int(args:List<String>):String{
    return "13" + jmpStuff(args)
}
fun addMore(opcode:Int, args:List<String>):String{
    return when(opcode){
        OpCodes.HALT.number -> padStrings(7)
        OpCodes.LOADI.number -> loadi(args)
        OpCodes.ADD.number -> add(args)
        OpCodes.PUSH.number -> push(args)
        OpCodes.POP.number -> pop(args)
        OpCodes.CMP.number -> cmp(args)
        OpCodes.JMPEQ.number -> jmpeq(args)
        OpCodes.SUB.number -> sub(args)
        OpCodes.MEMR.number -> memr(args)
        OpCodes.MEMW.number -> memw(args)
        OpCodes.JMP.number -> jmp(args)
        OpCodes.NOP.number -> nop()
        OpCodes.MUL.number -> mul(args)
        OpCodes.CALL.number -> call(args)
        OpCodes.RET.number -> ret()
        OpCodes.DIV.number -> div(args)
        OpCodes.DBG.number -> dbg()
        OpCodes.LOADA.number -> loada(args)
        OpCodes.LOADB.number -> loadb(args)
        OpCodes.INT.number -> int(args)
        OpCodes.PUSHL.number -> pushl(args)
        OpCodes.SINC.number -> stackInc(args)
        OpCodes.SDEC.number -> stackDec(args)
        OpCodes.RCUR.number -> rcur(args)
        OpCodes.WCUR.number -> wcur(args)
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