``` Bash
minishell$ echo =""
--------------------------------------------------------------------------------------------
|            content                          |    len   |      type      |     quote      |
--------------------------------------------------------------------------------------------
|{echo}                                       |       4  |       BUILTIN  |        QUOTE0  |
--------------------------------------------------------------------------------------------
|{=}                                          |       1  |          WORD  |        QUOTE0  |
--------------------------------------------------------------------------------------------
|{"}                                          |       1  |  DOUBLE_QUOTE  |        QUOTE0  |
--------------------------------------------------------------------------------------------

```

- [x] echo ""
- [x] echo " "
- [x] x="sdfsdf"
- [x] hello 
- [x] echo " (unclosed quote in the end of the file)