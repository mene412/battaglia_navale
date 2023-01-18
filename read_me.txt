Nel nostro progetto i sottomarini e le navi di supporto devono obbligatoriamente spostarsi nella griglia per poter effettuare l’azione, non possono rimanere nelle stesse celle. Per esempio, se abbiamo un sottomarino in E11, questo dovrà per forza compiere un movimento (es in E4 se non già occupata), altrimenti la mossa non è considerata valida e sarà da ripetere. 
I comandi speciali che abbiamo implementato sono:

-BB BB—> Cancella i caratteri relativi ai colpi andati a segno dalla griglia di attacco del giocatore

-CC CC—>Cancella i caratteri relativi ai colpi andati vuoto dalla griglia di attacco del giocatore

Come per i comandi AA AA (per cancellare gli avvistamenti sonar dalla griglia di difesa del giocatore) e XX XX (per visualizzare le due griglie del giocatore) questi comandi non “consumano” la mossa, ma devono essere effettuati prima di compiere un’azione con una propria nave. 
