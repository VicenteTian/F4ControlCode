/********************************
 * 
 * Notes:    Analyze the received data and draw the graph
 * 
 * 
 * 
 * 
 *******************************/
(

    function main() {
        var BytesNum = 2;//几个字节组成一个结果
        var isSign = false;
        var str = receive.get();          //Read the Received string
        var strstr="12"
        receive.write(str);               //Prints the received characters
        //receive.write(" -> ", "red");     //Print the arrow
        var buf = StrToBytes(str);        //Turn the received hex string into an array.
        var n = (buf.length - 4) / BytesNum;
        for (let index = 0; index < n; index++) {
            var val = BytesToValue(buf, 2 + BytesNum * index, BytesNum, isSign);  // 将两个8字节数字转化为16位有符号数
            receive.write(val + " ", "Green");//Print the converted integer
            chart.write("Line"+strstr[index]+"=" + val + "\n");  //Draw to waveform interface. The name is Real
        }
        receive.write("\r");            //Print line breaks for easy observation.
        return;
    }

)()

// 将两个8字节数字转化为16位有符号数
// index : The starting position in Bytes
function BytesToValue(buf, index, len, isSign) {
    var val = 0;
    var MySign = buf[index + len - 1] & 0x80;
    for (let i = 1; i <= len; i++) {
        val = val << 8;
        val = val + buf[index + len - i];
    }
    if (MySign && isSign) {
        val = (0xFFFFFFFF << 8 * len) | val;  // fill in most significant bits with 1's
    }
    return val;
}
//Turn the received hex string into an int array.
function StrToBytes(str) {
    var index = 0;
    var buf = new Array;
    for (var i = 0; i < str.length; i++) {
        while (str[i] == "«" || str[i] == " ") {  //Remove useless characters
            if (i < str.length)
                i++;
        }
        buf[index] = parseInt("0x" + str[i] + str[i + 1]);// Turn the string into a number.
        index++;
        i += 2;
    }
    return buf;
}
// Check the received data CRC
function check_crc(str) {

    var buf = StrToBytes(str);
    var index = buf.length;
    //Calculate the crc check value of the received data
    var crc1 = buf[index - 1] * 256 + buf[index - 2];

    //Calculate the received data check value.
    var crc = 0xFFFF;
    for (var i = 0; i < index - 2; i++) {
        crc ^= (buf[i] & 0x00FF);
        for (var j = 0; j < 8; j++) {
            if (crc & 0x01) {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }
    // receive.write(" crc1 0x" + crc1.toString(16));
    // receive.write(" crc2 0x" + crc.toString(16));

    if (crc1 == crc)
        return true;
    else
        return false;
}