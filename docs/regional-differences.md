There are five regional versions of Super Mario Galaxy 2:
- ``SB4E01``: North America
- ``SB4P01``: Europe/Australia
- ``SB4J01``: Japan
- ``SB4W01``: Asia (Taiwan, Hong Kong)
- ``SB4K01``: Korea

Unlike SMG1, all versions of SMG2 are pretty much identical. The key difference between all five versions is that the ``ErrorMessageArchive``'s files target only the languages accessible in the respective release. This of course results in shifted addresses for all data that follows the embedded archive. Aside from this, ``SB4E01``, ``SB4P01``, and ``SB4J01`` are identical.

After the release of these versions, a couple changes were made to target Asian regions. These changes are found in the ``SB4W01`` and ``SB4K01`` releases:

- A new language slot for Chinese using traditional characters called ``AsTradChinese`` was added.
- All functions from ``Language.cpp`` were updated to accomodate for the new language slot.
- The ``StafRoll`` functions were adjusted to work with the ``Kr`` and ``As`` region prefixes.
- An entry to preload ``/LayoutData/TimeUp.arc`` into ``StationedHeapGDDR3`` was added.
- ``SaveIconBanner.arc`` is now loaded from ``LayoutData`` instead of ``ObjectData``.
- ``LayoutCoreUtil::setTextBoxMessage`` was updated to subtract 0.5f in some yet-unidentified calculation.
- The Wiimote-related SDK libraries ``WPAD`` and ``KPAD`` were updated which resulted in some slight code changes.
- The following SDK libraries were rebuilt albeit with no changes aside from the build times being different:
  - AI
  - DSP
  - DVD
  - EXI
  - GX
  - LYT
  - NAND
  - OS
  - RFL
  - SC
  - SI
  - VI
