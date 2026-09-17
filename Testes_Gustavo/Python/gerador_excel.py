import pandas as pd
import tkinter as tk
from tkinter import filedialog
import os

def gerar_excel():
   
    root = tk.Tk()
    root.withdraw()

    
    caminho = filedialog.askopenfilename(
        title="selecionar txt",
        filetypes=[("Arquivos de Texto", "*.txt"), ("Todos os arquivos", "*.*")]
    )

    if not caminho:
        print("nenhum arquivo")
        return

    try:
        
        df = pd.read_csv(caminho, sep=';')
        
        
        excel = os.path.splitext(caminho)[0] + ".xlsx"

       
        with pd.ExcelWriter(excel, engine='openpyxl') as writer:
            df.to_excel(writer, index=False, sheet_name='saida')
            worksheet = writer.sheets['saida']
            
            for column in worksheet.columns:
                max_length = 0
                col_letter = column[0].column_letter
                for cell in column:
                    try:
                        if len(str(cell.value)) > max_length:
                            max_length = len(str(cell.value))
                    except:
                        pass
                worksheet.column_dimensions[col_letter].width = max_length + 2

        print(f"planilha gerada em {excel}")
        
       
        

    except Exception as e:
        print(f"{e}")

if __name__ == "__main__":
    gerar_excel()