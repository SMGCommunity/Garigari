import csv, datetime, glob, json, io, math, os, sys
from git import Repo
from pathlib import Path

import pandas as pd
import plotly.express as px

if "-graph" in sys.argv:
    doGraph = True

def truncate(number, digits) -> float:
    stepper = 10.0 ** digits
    return math.trunc(stepper * number) / stepper

full_game_size = 0
done_game_size = 0

with open("data/funcs.csv", "r") as f:
    lines = f.readlines()

    for line in lines:
        if "Symbol" in line:
            continue

        spl = line.split(",")
        sym = spl[0]
        size = int(spl[2], 16)
        match = spl[3].strip("\r\n")

        if match == "true":
            done_game_size += size

        full_game_size += size

print("Calculating percentages...")

progPercent = (done_game_size / full_game_size ) * 100.0
progNonPercent = int((done_game_size / full_game_size) * 120.0)

print(f"Progress: {progPercent}% [{done_game_size} / {full_game_size}] bytes")
print(f"You currently have {progNonPercent} / 120 stars.")
print("Generating JSON...")

json = []
json.append("{\n")
json.append("\t\"schemaVersion\": 1,\n")
json.append(f"\t\"label\": \"game\",\n")
json.append(f"\t\"message\": \"{progPercent}%\",\n")
json.append(f"\t\"color\": \"blue\"\n")
json.append("}")

with open(f"data/game.json", "w") as w:
    w.writelines(json)

if doGraph:
    print("Generating progress graph...")

    # now we do the cool progress drawing chart
    x_axis = [datetime.datetime.now()]
    y_axis = [progPercent]

    # np.seterr(all="ignore")

    repo = Repo(".")

    for commit in repo.iter_commits(rev='db207fd..main'):
        cur_file = None

        try:
            cur_file = commit.tree / 'data' / 'game.json'
        except:
            pass

        if cur_file is None:
            continue

        with io.BytesIO(cur_file.data_stream.read()) as f:
            try:
                percent_str = json.loads(f.read().decode('utf-8'))['message'].strip("%")
                x_axis.append(datetime.datetime.fromtimestamp(commit.committed_date))
                y_axis.append(float(percent_str))
            except:
                continue

    df = pd.DataFrame({'date': x_axis, 'progress': y_axis})
    fig = px.line(df, x='date', y='progress', title='Petari Progress', line_shape='hv', markers=False)
    fig.update_yaxes(ticksuffix='%')
    fig.write_image('prog.png')

print("Done.")