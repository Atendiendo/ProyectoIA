texfile = PlantillaEntrega1
bibfile = Referencias.bib

all: documento

documento: $(texfile).tex $(bibfile)
	pdflatex $(texfile).tex
	bibtex $(texfile)
	pdflatex $(texfile).tex
	pdflatex $(texfile).tex

clean:
	rm -f *~
	rm -f $(texfile).aux
	rm -f $(texfile).bbl
	rm -f $(texfile).blg
	rm -f $(texfile).log
	rm -f $(texfile).out
	rm -f $(texfile).tex.backup
	rm -f $(bibfile).backup