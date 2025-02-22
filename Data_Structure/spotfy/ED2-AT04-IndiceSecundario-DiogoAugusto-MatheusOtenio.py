#===========================================================================================================
#
#              Diogo Augusto Silverio Nascimento    2586460
#              Matheus Otenio                       2553139 
#
#
#              ED2-AT04-IndiceSecundario-DiogoAugusto-MatheusOtenio.py spotify-1M.csv query.txt saida.txt
#
#
#===========================================================================================================

import sys
import csv
import ast
import re
from collections import defaultdict

def main():
    if len(sys.argv) != 4:
        print("Erro: Número incorreto de argumentos.", file=sys.stderr)
        sys.exit(1)
    
    csv_filename, query_filename, output_filename = sys.argv[1], sys.argv[2], sys.argv[3]
    
    field_mapping = {
        'artist_name': 'artists',
        'name': 'name',
        'album': 'album',
        'year': 'year',
        'track_number': 'track_number',
        'disc_number': 'disc_number',
        'key': 'key',
        'mode': 'mode'
    }

    try:
        with open(csv_filename, 'r', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            headers = reader.fieldnames
            data = []
            data_ids = []
            id_to_index = {}
            for idx, row in enumerate(reader):
                data.append(row)
                song_id = row['id']
                data_ids.append(song_id)
                id_to_index[song_id] = idx
            if not data:
                with open(output_filename, 'w') as f:
                    f.write("Erro: arquivo de dados vazio.\n")
                return
    except FileNotFoundError:
        with open(output_filename, 'w') as f:
            f.write("Erro: arquivo de dados não encontrado.\n")
        return
    except Exception as e:
        with open(output_filename, 'w') as f:
            f.write(f"Erro ao ler o arquivo de dados: {str(e)}\n")
        return
    
    indexes = {
        'artists': defaultdict(list),
        'name': defaultdict(list),
        'album': defaultdict(list),
        'track_number': defaultdict(list),
        'disc_number': defaultdict(list),
        'key': defaultdict(list),
        'mode': defaultdict(list),
        'year': defaultdict(list)
    }

    for song in data:
        song_id = song['id']
        
        artists_str = song['artists']
        artists = []
        try:
            parsed_artists = ast.literal_eval(artists_str)
            if isinstance(parsed_artists, list):
                artists = [a.strip() for a in parsed_artists]
            else:
                artists = [str(parsed_artists).strip()]
        except:
            artists = [a.strip() for a in artists_str.split(',')]
        artists = [a for a in artists if a]
        for artist in artists:
            indexes['artists'][artist].append(song_id)
        
        name = song['name'].strip()
        indexes['name'][name].append(song_id)
        
        album = song['album'].strip()
        indexes['album'][album].append(song_id)
        
        track_number_str = song['track_number'].strip()
        try:
            track_number = int(track_number_str)
            indexes['track_number'][track_number].append(song_id)
        except ValueError:
            pass
        
        disc_number_str = song['disc_number'].strip()
        try:
            disc_number = int(disc_number_str)
            indexes['disc_number'][disc_number].append(song_id)
        except ValueError:
            pass
        
        key = song['key'].strip()
        indexes['key'][key].append(song_id)
        
        mode = song['mode'].strip()
        indexes['mode'][mode].append(song_id)
        
        year_str = song['year'].strip()
        try:
            year = int(year_str)
            indexes['year'][year].append(song_id)
        except ValueError:
            pass
    
    try:
        with open(query_filename, 'r', encoding='utf-8') as f:
            query_lines = f.read().splitlines()
    except FileNotFoundError:
        with open(output_filename, 'w') as f:
            f.write("Erro: arquivo de consulta não encontrado.\n")
        return
    except Exception as e:
        with open(output_filename, 'w') as f:
            f.write(f"Erro ao ler o arquivo de consulta: {str(e)}\n")
        return
    
    output_lines = []
    valid_fields = list(field_mapping.keys())
    
    for i in range(0, len(query_lines), 2):
        if i + 1 >= len(query_lines):
            output_lines.append("Erro: consulta incompleta.\n")
            break
        
        query_line = query_lines[i].strip()
        values_line = query_lines[i + 1].strip()
        
        parts = re.split(r'\s+(&|\|\|)\s+', query_line)
        fields = []
        operators = []
        
        for idx, part in enumerate(parts):
            if idx % 2 == 0:
                if part:
                    fields.append(part.strip())
            else:
                operators.append(part.strip())
        
        if not fields:
            output_lines.append("Erro: consulta vazia.\n")
            continue
            
        if len(operators) != len(fields) - 1:
            output_lines.append("Erro: formato de consulta inválido.\n")
            continue
            
        invalid_fields = [f for f in fields if f not in valid_fields]
        if invalid_fields:
            output_lines.append(f"Erro: campo(s) inválido(s) '{', '.join(invalid_fields)}'.\n")
            continue
            
        real_fields = [field_mapping[f] for f in fields]
        
        values = [v.strip() for v in values_line.split(',')]
        if len(values) != len(fields):
            output_lines.append("Erro: número de valores incorreto.\n")
            continue
            
        sets = []
        error = False
        for field, value in zip(real_fields, values):
            try:
                if field in ['year', 'track_number', 'disc_number']:
                    parsed_value = int(value)
                else:
                    parsed_value = value
                
                if field == 'artists':
                    ids = indexes['artists'].get(parsed_value, [])
                else:
                    ids = indexes[field].get(parsed_value, [])
                sets.append(set(ids))
                
            except ValueError:
                output_lines.append(f"Erro: valor inválido '{value}' para campo '{field}'.\n")
                error = True
                break
            except KeyError:
                output_lines.append(f"Erro: campo '{field}' não encontrado nos índices.\n")
                error = True
                break
        
        if error:
            continue
            
        if not sets:
            result = set()
        else:
            current_sets = [sets[0]]
            current_ops = []
            for i in range(len(operators)):
                op = operators[i]
                next_set = sets[i + 1]
                if op == '&':
                    combined = current_sets[-1].intersection(next_set)
                    current_sets[-1] = combined
                else:
                    current_sets.append(next_set)
                    current_ops.append(op)
            
            if not current_sets:
                result = set()
            else:
                result = current_sets[0]
                for i in range(len(current_ops)):
                    result = result.union(current_sets[i + 1])
        
        sorted_ids = sorted(result, key=lambda x: id_to_index[x])
        
        if not sorted_ids:
            output_lines.append("Nenhum resultado foi encontrado!\n")
        else:
            for song_id in sorted_ids:
                song_data = data[id_to_index[song_id]]
                output_lines.append(','.join(song_data.values()) + '\n')
    
    try:
        with open(output_filename, 'w', encoding='utf-8') as f:
            f.writelines(output_lines)
    except Exception as e:
        print(f"Erro ao escrever saída: {str(e)}", file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()