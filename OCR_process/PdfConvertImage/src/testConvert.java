import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.rendering.PDFRenderer;

public class testConvert {

	public static void main (String[] args) {
		// TODO Auto-generated method stub
		String filePath = "E:/OCR_process/data/word_data.pdf";
		File file = new File(filePath);
		try {
			PDDocument doc = PDDocument.load(file);
			PDFRenderer renderer = new PDFRenderer(doc);
			int pageCount = doc.getNumberOfPages();
			for(int i=0;i<pageCount;i++){
				BufferedImage image = renderer.renderImageWithDPI(i, 296);
				String saveFilePath = "E:/OCR_process/data/img_tif/";
				saveFilePath += "image";
				saveFilePath += "_";
//				saveFilePath += filePath;
				saveFilePath += "_";
				saveFilePath += i;
				saveFilePath += ".tif";
				System.out.println("saveFilePath = " + saveFilePath);
				ImageIO.write(image, "tif", new File(saveFilePath));
			}
		}catch (IOException e) {
			e.printStackTrace();
		}
	}

}
