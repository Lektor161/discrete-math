package main

import "strings"
import "fmt"

func escape(s string) string {
    var result string
    for _, element := range s {
        if (element == '\n') {
            result += "\\n"
        } else if element == '"' {
            result += "\\\""
        } else if (element == '\\') {
            result += "\\\\"
        } else {
            result += string(element)
        }
    }
    return result
}

func main() {
    var ind int
    fmt.Scan(&ind);
    var result string = "$"
    for i := 0; i < ind; i++ {
        result = escape(result);
        result = "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"" + result;
        result = result + "\")\n}"
    }
    fmt.Print(strings.Replace(result, "$", "", -1))
}
