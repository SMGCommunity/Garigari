"""Render every report unit and function; input is a verified local snapshot."""
import json, html
from pathlib import Path
p=Path(__file__).resolve().parents[1]
r=json.loads((p/'docs/progress/snapshot.json').read_text())
colors=['#22c55e','#38bdf8','#f59e0b','#334155']
def layout(items,x,y,w,h):
 if not items:return
 if len(items)==1:
  yield items[0],x,y,w,h;return
 total=sum(a[0] for a in items);acc=0;k=1
 for i,a in enumerate(items[:-1]):
  acc+=a[0];k=i+1
  if acc>=total/2:break
 f=acc/total
 if w>=h:
  yield from layout(items[:k],x,y,w*f,h);yield from layout(items[k:],x+w*f,y,w*(1-f),h)
 else:
  yield from layout(items[:k],x,y,w,h*f);yield from layout(items[k:],x,y+h*f,w,h*(1-f))
svg=['<svg xmlns="http://www.w3.org/2000/svg" width="1800" height="1200" viewBox="0 0 1800 1200">','<rect width="1800" height="1200" fill="#0f172a"/>','<g font-family="sans-serif" fill="white"><text x="20" y="30" font-size="22">Garigari SB4E01 — all units and functions</text>',f'<text x="20" y="55" font-size="14">{r["integrated"]:,} / {r["total"]:,} code bytes source-linked ({100*r["integrated"]/r["total"]:.5f}%) · full retail DOL byte identity verified</text>']
for i,t in enumerate(['Source-linked','Exact, original-linked','Partial, original-linked','Unreconstructed']):svg.append(f'<rect x="{20+i*430}" y="72" width="14" height="14" fill="{colors[i]}"/><text x="{40+i*430}" y="85" font-size="14">{t}</text>')
svg.append('</g>'); paths=[[] for _ in colors];borders=[]
for (_,u),x,y,w,h in layout(sorted([(max(1,u['bytes']),u) for u in r['units']],key=lambda a:-a[0]),10,105,1780,1085):
 fs=u['functions']; linked=u['linked']
 for (_,f),fx,fy,fw,fh in layout(sorted([(max(1,f[1]),f) for f in fs],key=lambda a:-a[0]) or [(1,['data',1,0])],x,y,w,h):
  c=0 if linked and fs else 1 if f[2]==100 else 2 if f[2]>0 else 3
  paths[c].append(f'M{fx:.1f},{fy:.1f}h{fw:.1f}v{fh:.1f}h-{fw:.1f}z')
 title=html.escape(u['name']+f' — {len(fs)} functions; {u["bytes"]} code/data bytes')
 borders.append(f'<rect x="{x:.1f}" y="{y:.1f}" width="{w:.1f}" height="{h:.1f}" fill="transparent" stroke="#94a3b8" stroke-width=".35"><title>{title}</title></rect>')
for c,ps in zip(colors,paths):svg.append(f'<path d="{"".join(ps)}" fill="{c}" stroke="#0f172a" stroke-width=".12"/>')
svg+=borders+['</svg>'];(p/'docs/progress/treemap.svg').write_text('\n'.join(svg))
# Searchable full function inventory complements the dense README map.
rows=[]
for u in r['units']:
 rows.append('<details><summary>'+html.escape(u['name'])+f' ({len(u["functions"])} functions)</summary><table>')
 for n,size,match in u['functions']:rows.append('<tr><td>'+html.escape(n)+f'</td><td>{size} B</td><td>{match:.2f}%</td><td>'+('source-linked' if u['linked'] else 'original-linked')+'</td></tr>')
 rows.append('</table></details>')
(p/'docs/progress/functions.html').write_text('<!doctype html><meta charset="utf-8"><title>Garigari function inventory</title><style>body{font:14px system-ui;background:#0f172a;color:#eee}td{padding:4px 12px}summary{cursor:pointer}</style><h1>All units and functions</h1><p>Exact similarity does not prove relocation fidelity or integration. Source-linked status follows verified unit selection.</p>'+''.join(rows))
