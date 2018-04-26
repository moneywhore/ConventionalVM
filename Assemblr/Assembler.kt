import com.sun.scenario.effect.LinearConvolveCoreEffect
import java.io.File

var labels = HashMap<String,Int>()
var calcOrigin:Int = 0


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
    INT(19),
    PUSHL(20),
    SINC(21),
    SDEC(22),
    RCUR(23),
    WCUR(24),
    CALLI(25),
    ORIGIN(26)
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
        "PUSHL" -> Opcodes.PUSHL.number
        "SINC" -> Opcodes.SINC.number
        "SDEC" -> Opcodes.SDEC.number
        "RCUR" -> Opcodes.RCUR.number
        "WCUR" -> Opcodes.WCUR.number
        "CALLI" -> Opcodes.CALLI.number
        "ORG" -> Opcodes.ORIGIN.number
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

fun mathOpCode(args:List<String>):String {
    val register1 = args[1].replace("R","")
    val register2 = args[2].replace("R","")
    val register3 = args[3].replace("R","")
    return  register1 + register2 + register3 + padStrings(2)
}

fun justImm(args:List<String>):String{
    val register = args[1].replace("R","")
    var imm = args[2]
    if (args[2].startsWith("%")) {
        imm = imm.replace("%", "")
        return "01" + register + padStrings(4 - imm.length) + imm
    }
    val hexValue = Integer.toHexString(imm.toInt())
    return register + padStrings(4 - hexValue.length) + hexValue
}

fun loadi(args:List<String>):String {

    return "01" + justImm(args)
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
    address = Integer.toHexString(address.toInt() + calcOrigin)
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

fun calli(args:List<String>):String{
    return "19" + justImm(args)
}

fun offset(args:List<String>):String{
    calcOrigin = args[0].toInt()
    return nop()
}

fun addMore(opcode:Int, args:List<String>):String{
    return when(opcode){
        Opcodes.HALT.number -> padStrings(7)
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
        Opcodes.DIV.number -> div(args)
        Opcodes.DBG.number -> dbg()
        Opcodes.LOADA.number -> loada(args)
        Opcodes.LOADB.number -> loadb(args)
        Opcodes.INT.number -> int(args)
        Opcodes.PUSHL.number -> pushl(args)
        Opcodes.SINC.number -> stackInc(args)
        Opcodes.SDEC.number -> stackDec(args)
        Opcodes.RCUR.number -> rcur(args)
        Opcodes.WCUR.number -> wcur(args)
        Opcodes.CALLI.number -> calli(args)
        Opcodes.ORIGIN.number -> offset(args)
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

fun removeComments(asm:List<String>):List<String>{
    var returnAsm = mutableListOf<String>()
    for(line in asm){
        var hasComment = line.indexOf(";")
        if(hasComment >= 0) {
            val newLine = line.removeRange(line.indexOf(";"), line.length)
            if(newLine!= ""){
                returnAsm.add(newLine)
            }
        }else{
            returnAsm.add(line)
        }

    }
    return returnAsm
}

fun calculateLabelAddress(code:List<String>):List<String>{
    var lineCounter = -1
    var labelLessCode = mutableListOf<String>()
    val regex = Regex("[ :,]")
    for(line in code){
        lineCounter++
        if(line.toLowerCase().startsWith("label")){
            val labelName = line.toLowerCase().split(regex)
            labels.put(labelName[1],lineCounter)
            val lineNew = "nop"
            labelLessCode.add(lineNew)
        }else{
            labelLessCode.add(line)
        }
    }
    return labelLessCode
}

fun updateWithProperLocation(code:List<String>):List<String>{
    var finalVersion = mutableListOf<String>()
    val regex = Regex("[ :,]")
    for(line in code){
        var newLine = ""
        for(key in labels.keys){
            val lineData = line.toLowerCase().split(regex)
            for(parts in lineData){
                if(parts == key){
                    newLine += labels[key].toString()
                }else{
                    newLine += parts + " "
                }
            }
        }
        finalVersion.add(newLine)
    }
    return finalVersion
}

fun main(arg:Array<String>){
    var filename= "code.asm"
    if(arg.size > 1){
        filename = arg[0]
    }
    print(filename)
    val codeFile = File(filename)
    val code = codeFile.readLines()

    val withoutComments = removeComments(code)
    val labellessCode = calculateLabelAddress(withoutComments)
    labellessCode.forEach({ println(it)})
    val finalCode = updateWithProperLocation(labellessCode)
    println("\n\n")
    finalCode.forEach({ println(it)})
    val output = assemble(finalCode)
    val outputText = File("code.txt")
    outputText.writeText(output)
}
