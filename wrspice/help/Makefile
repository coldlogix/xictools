# wrspice/lib/help/Makefile

BASEFILES = FileSel.hlp Hardcopy.hlp TMsmall.gif
MOZYFILES = HelpSys.hlp TextEditor.hlp

SPFILES = \
  spAnalysis.hlp spElements.hlp spExpressions.hlp spInput.hlp spModels.hlp \
  spSemicond.hlp spSources.hlp

BASE = ../../xt_base/help
SPBASE = ../../xt_base/sphelp
MOZY = ../../mozy/help

depend: $(BASEFILES) $(MOZYFILES) $(SPFILES)
	cd screenshots; $(MAKE)

$(BASEFILES):
	cp -fp $(BASE)/$@ .

$(MOZYFILES):
	cp -fp $(MOZY)/$@ .

$(SPFILES):
	cp -fp $(SPBASE)/$@ .

FileSel.hlp:    $(BASE)/FileSel.hlp
Hardcopy.hlp:   $(BASE)/Hardcopy.hlp
TMsmall.gif:    $(BASE)/TMsmall.gif
HelpSys.hlp:    $(MOZY)/HelpSys.hlp
TextEditor.hlp: $(MOZY)/TextEditor.hlp

spAnalysis.hlp: $(SPBASE)/spAnalysis.hlp
spElements.hlp: $(SPBASE)/spElements.hlp
spExpressions.hlp: $(SPBASE)/spExpressions.hlp
spInput.hlp:    $(SPBASE)/spInput.hlp
spModels.hlp:   $(SPBASE)/spModels.hlp
spSemicond.hlp: $(SPBASE)/spSemicond.hlp
spSources.hlp:  $(SPBASE)/spSources.hlp

clean:

distclean:
	-@rm -f $(BASEFILES) $(MOZYFILES) $(SPFILES)
	-@cd screenshots; $(MAKE) distclean

# Look for forms like <a href="something>, some browsers can't handle
# a missing trailing quote.
check::
	-egrep 'href="[^>"]+>' *.hlp

