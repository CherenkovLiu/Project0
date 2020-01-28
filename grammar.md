```
<program> := <functions> EOF
<functions> := null | <function> <functions>
<function> := def identifier ( <declarations> ) : <type> = <statements>
<declarations> := null | <declaration> , <declarations>
<declaration> := identifier : <type>
<type> := <type_id> <is_array>
<type_id> := buildin_type | identifier
<is_array> := null | [ <size> ]
<size> := null | number
<statements> := null | <statement> <statements>
<statement> := <block> | <if> | <while> | <assign_statement> | <return> | <reassign_state>
<block> := { <statements> }
<return> := return <expr> ;
<if> := if ( <expr> ) <statement> <else_statement>
<else_statement> := null | else <statement>
<while> := while ( <expr> ) <statement>
<assign_statement> := let <assigns> ;
<assigns> := null | <assign> , <assigns>
<assign> := <declarations> = <right_value>
<right_value> := <expr>
<reassign_state> := identifier <assign_operators> <right_value> ;
<assign_operators> := = | += | -= | *= | /= | &= | |= | %= 
```