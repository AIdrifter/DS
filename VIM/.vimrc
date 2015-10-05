# reomve extra "sapce"
call setline(1,map(getline(1,"$"),'substitute(v:val,"\\s\\+$","","")'))
